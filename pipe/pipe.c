#include "../includes/minishell.h"

int	run_cmd(void)
{
	if (g_info.cmds[1] == NULL && is_builtin(g_info.cmds[0][0]))
	{
		return (run_only_one_cmd(0));
	}
	else
	{
		return (run_pipe());
	}
	return (0);
}

int	is_builtin(char *str)
{
	return (!ft_strcmp(g_info.cmds[0][0], "echo") || !ft_strcmp(g_info.cmds[0][0], "cd")
		|| !ft_strcmp(g_info.cmds[0][0], "pwd") || !ft_strcmp(g_info.cmds[0][0], "export")
		|| !ft_strcmp(g_info.cmds[0][0], "unset") || ft_strcmp(g_info.cmds[0][0], "env")
		|| !ft_strcmp(g_info.cmds[0][0], "exit"));
}

////////////////////////////////////////////////
// pipe.c 컴파일 되게 하기 위해 임시로 넣어놓은 함수 프로토타입부분
// 
int		builtin_echo(int i);
int		builtin_cd(int i);
int		builtin_pwd(int i);
int		builtin_export(int i);
int		builtin_unset(int i);
int		builtin_env(int i);
int		builtin_exit(int i);

////////////////////////////////////

int	run_only_one_cmd(int i)
{
	if (ft_strcmp(g_info.cmds[i][0], "echo") == 0)
	{
		return (builtin_echo(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "cd") == 0)
	{
		return (builtin_cd(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "pwd") == 0)
	{
		return (builtin_pwd(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "export") == 0)
	{
		return (builtin_export(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "unset") == 0)
	{
		return (builtin_unset(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "env") == 0)
	{
		return (builtin_env(i));
	}
	else if (ft_strcmp(g_info.cmds[i][0], "exit") == 0)
	{
		return (builtin_exit(i));
	}
	return (1);
}

///////////////////////////////////////////////////////////

static void	copy_pipe_fd(int a[], int b[]){
	a[0] = b[0];
	a[1] = b[1];
}

int	run_pipe(void)
{
	int pipe0[2];
	int pipe1[2];
	int stat;
	int inputfd;
	int outputfd;
	int fd;
	int	*child_stat; // waitpid에서 각각 받아올 종료 stat의 배열

	child_stat = (int *)malloc(sizeof(int) * num_of_cmd());
	if (child_stat == NULL)
	{
		ft_perror("pipe");
		return (1);
	}


	// int	last = 9; // 커맨드 갯수
	int i = -1;

	while (g_info.cmds[++i] != NULL){
		// if (idx == last){
		// 	break ;
		// }
		pipe(pipe1);
		fd = fork();
		if (fd == 0)
		{ // child
		// 공통

			// 기본 input셋팅
			///////////////////////
			if (i != 0){
				close(pipe0[1]);
				dup2(pipe0[0], 0);
			}
//////////////////////////////

		// input redirection
			inputfd = check_input_redirection(i, pipe1); // readend는 닫힌 상태
			if (inputfd < 0)
			{
				print_error(inputfd, g_info.cmds[i][0]);
				exit(1);
			}
		////////////////////////////




			// 기본 output 셋팅
			// 여길 나중에 해줘야 "<<"입력 받을 때 stdout으로 "> "대기 프롬프트를 띄워줄 수 있음
			close(pipe1[0]);
			if (g_info.cmds[i + 1] == NULL){
				close(pipe1[1]);
			}else{
				dup2(pipe1[1], 1);
			}
			////////////////////////
		// output redirectio
			outputfd = check_output_redirection(i, pipe1);
			if (outputfd < 0)
			{
				print_error(outputfd, g_info.cmds[i][0]);
				exit(1);
			}


			try_builtin_or_execve(i);
		}
		else if (fd > 0)
		{
			// parent
			if (i != 0){
				close(pipe0[0]);
				close(pipe0[1]);
			}
			copy_pipe_fd(pipe0, pipe1);
			waitpid(fd, &child_stat[i], WNOHANG); // 각 자식 프로세스마다 wait
			++i;
		}
		else
		{
			ft_perror("fork");
			return (1);
		}
	}
	return(WEXITSTATUS(child_stat[--i])); // 맨 마지막 커맨드의 종료 상태 반환
}
/////////////////////////////////////////

int		check_input_redirection(int i, int pip[])
{
	t_list	*node;
	t_list	*node_of_redir_list;
	int		ret;
	int		read_size;
	char	buf[BUF_SIZE];

	node = find_node_at_idx_in_list(g_info.cmd_redir_lst, i);
	if (node == NULL)
		return (REDIR_INFO_NODE_NOT_FOUND);
	node_of_redir_list = node->data;
	while (node_of_redir_list != NULL)
	{
		if (node_of_redir_list->data == NULL)
			return (REDIR_INFO_NODE_NULL);
		if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == IN_REDIR_LIM) // "<<"의 리디렉션
		{

			close(pip[0]); // 기존 파이프 read end도 닫아서 완전히 닫기
			close(0); // dup2했던 것도 닫아줘야 완전히 닫힘
			pipe(pip);
			dup2(pip[0], 0);

			write(STDOUT_BACKUP_FD, "> ", 2);
			read_size = read(STDIN_BACKUP_FD, buf, BUF_SIZE);
			while (read_size > 0)
			{
				if (ft_strncmp(((t_redir_lst_nod*)(node_of_redir_list))->path, buf, read_size) == 0)
					break ;
				write(pip[1], buf, read_size);
				write(STDOUT_BACKUP_FD, "> ", 2);
				read_size = read(STDIN_BACKUP_FD, buf, BUF_SIZE);
			}
			if (read_size < 0)
			{
				return (READ_ERROR);
			}
			close(pip[1]);
		}
		else if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == IN_REDIR)
		{
			close(pip[0]);
			close(0);
			pip[0] = open(((t_redir_lst_nod*)(node_of_redir_list->data))->path, O_RDONLY);
			if (pip[0] < 0)
			{
				return (OPEN_ERROR);
			}
			dup2(pip[0], 0);

		}
		node_of_redir_list = node_of_redir_list->next;
	}
}

// void	count_input_redirections(int i, int *input_cnt, t_list *node)
// {
// 	while (node)
// 	{
// 		if (((t_redir_lst_nod*)(node->data))->type == IN_REDIR)
// 			++(*input_cnt);
// 		else if (((t_redir_lst_nod*)(node->data))->type == IN_REDIR_LIM)
// 			++(*input_cnt);
// 		node = node->next;
// 	}
// }

int		check_output_redirection(int i, int pip[])
{
	t_list	*node;
	t_list	*node_of_redir_list;
	int		ret;
	int		read_size;
	int		buf[BUF_SIZE];

	node = find_node_at_idx_in_list(g_info.cmd_redir_lst, i);
	if (node == NULL)
		return (REDIR_INFO_NODE_NOT_FOUND);
	node_of_redir_list = node->data;
	while (node_of_redir_list != NULL)
	{
		if (node_of_redir_list->data == NULL)
			return (REDIR_INFO_NODE_NULL);
		if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == OUT_REDIR_APP
			|| ((t_redir_lst_nod*)(node_of_redir_list->data))->type == OUT_REDIR) // ">"또는 ">>"의 리디렉션
		{
			close(pip[1]);
			close(1);
			if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == OUT_REDIR_APP)
				pip[1] = open(((t_redir_lst_nod*)(node_of_redir_list->data))->path, O_WRONLY | O_CREAT | O_APPEND, OUT_REDIR_PERMISSION_BIT);
			else
				pip[1] = open(((t_redir_lst_nod*)(node_of_redir_list->data))->path, O_WRONLY | O_CREAT | O_TRUNC, OUT_REDIR_PERMISSION_BIT);
			if (pip[1] < 0)
			{
				return (OPEN_ERROR);
			}
			dup2(pip[1], 1);
		}
		node_of_redir_list = node_of_redir_list->next;
	}
}

//////////////////////////////

/*
**	void try_builtin_or_execve(int i);
*/
// 빌트인이면 빌트인 함수 실행
// 실행 파일이면 현재 경로부터 PATH까지 붙여서 execve시도
void	try_builtin_or_execve(int i)
{
	char	*tmp;
	int		error_check;

	if (is_builtin(g_info.cmds[i][0]))
		exit(run_only_one_cmd(i));
	else
	{
		tmp = pipe_strjoin(".", "/", g_info.cmds[i][0]);
		if (tmp == NULL)
		{
			ft_perror(g_info.cmds[i][0]); // free는 main에서 해준다.리턴만 해주자.
			exit(1);
		}
		execve(tmp, g_info.cmds[i], g_info.envp);
		free(tmp);
		error_check = try_builtin_or_execve_sub(i);
	}
	print_error(error_check, g_info.cmds[i][0]); // 에러 문구 출력은 여기서만
	exit(1);
}

int		try_builtin_or_execve_sub(int i)
{
	int		path_idx;
	int		path_string_idx;
	char	*tmp;

	path_idx = find_index_of_path_in_env();
	if (path_idx < 0)
		return (CMD_NOT_FOUND);
	path_string_idx = 5;
	while (g_info.envp[path_idx][path_string_idx] != '\0')
	{
		tmp = try_builtin_or_execve_sub2(&path_string_idx, path_idx, i);
		if (tmp == NULL)
		{
			return (MALLOC_ERROR);
		}
		execve(tmp, g_info.cmds[i], g_info.envp);
		free(tmp);
	}
	return (CMD_NOT_FOUND);
}

// PATH변수에서 path_string_idx에 있는 글자부터 ':' 또는 널문자 나올 때까지 있는 스트링을 동적 할당해서 반환
// ':'을 만났다면 path_string_idx를 ':' 다음 글자로 설정,
// 		널문자를 만났다면 그냥 널문자 자리로 설정해준다.
char	*try_builtin_or_execve_sub2(int *path_string_idx, int path_idx, int i)
{
	int		end_idx;
	char	*tmp;
	char	*ret;

	end_idx = *path_string_idx;
	while (g_info.envp[path_idx][end_idx] != ':' && g_info.envp[path_idx][end_idx] != '\0')
		++end_idx;
	tmp = ft_strndup(g_info.envp[path_idx] + (*path_string_idx), end_idx - *path_string_idx);
	if (tmp == NULL)
		return (NULL);
	ret = pipe_strjoin(tmp, "/", g_info.cmds[i][0]);
	free(tmp);
	if (ret == NULL)
		return (NULL);
	if (g_info.envp[path_idx][end_idx] == ':')
		*path_string_idx = end_idx + 1;
	else
		*path_string_idx = end_idx;
	return (ret);
}

int		find_index_of_path_in_env(void)
{
	int	i;

	i = -1;
	while (g_info.envp[++i] != NULL)
	{
		if (ft_strncmp(g_info.envp[i], "PATH=", 5) == 0) // "PATH="까지 다섯 글자
			return (i);
	}
	return (-1);
}

char	*pipe_strjoin(char *s1, char *s2, char *s3)
{
	int		len;
	char	*ret;
	char	*temp1;

	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	temp1 = ft_strjoin(s1, s2);
	if (!temp1)
		return (NULL);
	ret = ft_strjoin(temp1, s3);
	free(temp1);
	if (!ret)
		return (NULL);
	len += 1;
	return (ret);
}
