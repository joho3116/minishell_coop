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
	// int	ret =(!ft_strcmp(g_info.cmds[0][0], "echo") || !ft_strcmp(g_info.cmds[0][0], "cd")
	// 	|| !ft_strcmp(g_info.cmds[0][0], "pwd") || !ft_strcmp(g_info.cmds[0][0], "export")
	// 	|| !ft_strcmp(g_info.cmds[0][0], "unset") || !ft_strcmp(g_info.cmds[0][0], "env")
	// 	|| !ft_strcmp(g_info.cmds[0][0], "exit"));
	// printf("\nret %s = %d\n", str, ret);
	return (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "pwd") || !ft_strcmp(str, "export")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "exit"));
}

////////////////////////////////////////////////
// pipe.c 컴파일 되게 하기 위해 임시로 넣어놓은 함수 프로토타입부분
//
// int		builtin_echo(int i);
// int		builtin_cd(int i);
// int		builtin_pwd(int i);
// int		builtin_export(int i);
// int		builtin_unset(int i);
// int		builtin_env(int i);
// int		builtin_exit(int i);

////////////////////////////////////

int	run_only_one_cmd(int i)
{
	if (is_builtin(g_info.cmds[i][0]))
		return (run_only_one_cmd_builtin(i));
	else
		return (run_only_one_cmd_not_builtin(i));
}

int	run_only_one_cmd_builtin(int i)
{
	int	not_pipe[2];
	int	error_check;
	int	ret;

	not_pipe[0] = 0;
	not_pipe[1] = 1;
	error_check = check_input_redirection(i, not_pipe);
	if (error_check < 0)
	{
		error_check = restore_stdin_stdout();
		print_error(error_check, g_info.cmds[i][0]);
		return (error_check);
	}
	error_check = check_output_redirection(i, not_pipe);
	if (error_check < 0)
	{
		error_check = restore_stdin_stdout();
		print_error(error_check, g_info.cmds[i][0]);
		return (error_check);
	}

	if (ft_strcmp(g_info.cmds[i][0], "echo") == 0)
	{
		// debug
		// printf("echo in\n");////////////////////////////////
		ret = builtin_echo(i);
	}
	else if (ft_strcmp(g_info.cmds[i][0], "cd") == 0)
	{
		ret = builtin_cd(i);
	}
	else if (ft_strcmp(g_info.cmds[i][0], "pwd") == 0)
	{
		ret = builtin_pwd(i);
	}
	else if (ft_strcmp(g_info.cmds[i][0], "export") == 0)
	{
		ret = builtin_export(i);
	}
	else if (ft_strcmp(g_info.cmds[i][0], "unset") == 0)
	{
		ret = builtin_unset(i);
	}
	else if (ft_strcmp(g_info.cmds[i][0], "env") == 0)
	{
		ret = builtin_env(i);
	}
	// else if (ft_strcmp(g_info.cmds[i][0], "exit") == 0)
	// {
	// 	ret = builtin_exit(i);
	// }
	error_check = restore_stdin_stdout(); // 리디렉션 복구
	if (error_check < 0)
	{
		print_error(error_check, g_info.cmds[i][0]);
		return (error_check);
	}
	return (ret);
}

int	run_only_one_cmd_not_builtin(int i)
{
	int	pid;
	int	stat;
	int	not_pipe[2];
	int	error_check;

	pid = fork();
	if (pid == 0)
	{
		try_builtin_or_execve(i);
		return (0);
	}
	else if (pid > 0)
	{
		waitpid(pid, &stat, 0);
		return (WEXITSTATUS(stat));
	}
	else
	{
		ft_perror(g_info.cmds[i][0]);
		return (1);
	}
}

///////////////////////////////////////////////////////////

static void	copy_pipe_fd(int a[], int b[]){
	a[0] = b[0];
	a[1] = b[1];
}

int	num_of_cmd(void)
{
	int	cnt;

	cnt = -1;
	while (g_info.cmds[++cnt] != NULL)
		;
	return (cnt);
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

	signal(SIGINT, sig_handler_on_main_at_run_cmd);
	signal(SIGQUIT, sig_handler_on_main_at_run_cmd);

	// int	last = 9; // 커맨드 갯수
	int i = -1;
	pipe0[0] = 0;
	pipe0[1] = 1;
	while (g_info.cmds[++i] != NULL){
		// if (idx == last){
		// 	break ;
		// }
		// ft_putstr_fd("|", 2);//////////////////
		// ft_putstr_fd(g_info.cmds[i][0], 2);//////////
		// ft_putstr_fd("|", 2);/////////////////
		// ft_putstr_fd("\n", 2);/////
		pipe(pipe1);
		fd = fork();

		if (fd == 0)
		{ // child
		// 공통
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			// 기본 input셋팅
			///////////////////////
			if (i != 0){
				close(pipe0[1]);
				dup2(pipe0[0], 0);
			}
			//////////////////////////////

			// input redirection
			inputfd = check_input_redirection(i, pipe0); // readend는 닫힌 상태
			if (inputfd < 0)
			{
				// printf("here\n");
				print_error(inputfd, g_info.cmds[i][0]);
				exit(1);
			}
			////////////////////////////

			//debug
			// write(1, "input_redirec_Fin\n", ft_strlen("input_redirec_Fin\n"));  //////////////debug



			// 기본 output 셋팅
			// 여길 나중에 해줘야 "<<"입력 받을 때 stdout으로 "> "대기 프롬프트를 띄워줄 수 있음
			close(pipe1[0]);
			if (g_info.cmds[i + 1] == NULL){
				close(pipe1[1]);
				// ft_putstr_fd(g_info.cmds[i][0], 1);//////////debug
				// ft_putstr_fd("\n\nsfsfsfs", 1); //////////////debug
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
			if (g_info.cmds[i + 1] == NULL)
				waitpid(fd, &child_stat[i], 0); // 마지막 프로세스는 대기
			else
				waitpid(fd, &child_stat[i], WNOHANG); // 각 자식 프로세스마다 wait
		}
		else
		{
			ft_perror("fork");
			return (1);
		}
	}
	stat = WEXITSTATUS(child_stat[--i]);
	free(child_stat);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	return(stat); // 맨 마지막 커맨드의 종료 상태 반환
}
/////////////////////////////////////////

int		restore_stdin_stdout(void)
{
	if (dup2(STDIN_BACKUP_FD, 0) < 0)
	{
		ft_perror("dup2");
		return (STD_FD_RESTORE_FAIL);
	}
	if (dup2(STDOUT_BACKUP_FD, 1) < 0)
	{
		ft_perror("dup2");
		return (STD_FD_RESTORE_FAIL);
	}
	return (0);
}
int		check_input_redirection(int i, int pip[])
{
	t_list	*node;
	t_list	*node_of_redir_list;
	int		ret;
	int		read_size;
	char	buf[BUF_SIZE];
	char *line;

	node = find_node_at_idx_in_list(g_info.cmd_redir_lst, i);
	if (node == NULL)
		return (REDIR_INFO_NODE_NOT_FOUND);
	node_of_redir_list = node->data;
	while (node_of_redir_list != NULL)
	{
		// ft_putstr_fd("in\n", 2);
		if (node_of_redir_list->data == NULL)
			return (REDIR_INFO_NODE_NULL);
		if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == IN_REDIR_LIM) // "<<"의 리디렉션
		{

			close(pip[0]); // 기존 파이프 read end도 닫아서 완전히 닫기
			if (pip[0] != 0)
				close(0); // dup2했던 것도 닫아줘야 완전히 닫힘
			pipe(pip);
			if (pip[0] == 0)
			{
				pip[0] = dup(pip[0]);
				close(0);
			}
			dup2(STDIN_BACKUP_FD, 0);

			while (1)
			{
				line = readline("> ");
				if (!line)
				{
					// write(1, "\n", 1);
					break ;
				}
				if (ft_strcmp(((t_redir_lst_nod *)(node_of_redir_list->data))->path, line) == 0)
				{
					// write(STDOUT_BACKUP_FD, "if", 2);//////////////debug
					free(line);
					break ;
				}
				// printf("line = %s\n", line);
				// printf("pip[1] = %d\n", pip[1]);
				write(pip[1], line, ft_strlen(line));
				write(pip[1], "\n", 1);
				free(line);
			}
			close(pip[1]);
			dup2(pip[0], 0);
		}
		else if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == IN_REDIR)
		{
			close(pip[0]);
			if (pip[0] != 0)
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
	return (0);
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
		// ft_putstr_fd("in\n", 2);
		if (node_of_redir_list->data == NULL)
			return (REDIR_INFO_NODE_NULL);
		if (((t_redir_lst_nod*)(node_of_redir_list->data))->type == OUT_REDIR_APP
			|| ((t_redir_lst_nod*)(node_of_redir_list->data))->type == OUT_REDIR) // ">"또는 ">>"의 리디렉션
		{
			close(pip[1]);
			if (pip[1] != 1)
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
	return (0);
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
	char	**envp;

	// ft_putstr_fd(g_info.cmds[i][0], 2);//////////////////////////////
	// printf("is builtin = %d\n", is_builtin(g_info.cmds[i][0]));/////////////////
	if (is_builtin(g_info.cmds[i][0]))
	{
		// printf("try builtin에서 빌트인\n");
		exit(run_only_one_cmd_builtin(i));
	}
	else
	{
		// ft_putstr_fd("herer\n", 2);//////////
		envp = get_env_list();
		if (envp == NULL)
		{
			ft_perror(g_info.cmds[i][0]);
			exit(1);
		}
		if (g_info.cmds[i][0][0] == '/' || g_info.cmds[i][0][0] == '.')
		{
			execve(g_info.cmds[i][0], g_info.cmds[i], envp);
			ft_putstr_fd("minishell: ", 2);
			ft_perror(g_info.cmds[i][0]);
			exit(127); // 테스트 결과
		}
		error_check = try_builtin_or_execve_sub(i, envp);
	}
	free_envp_list(envp);
	print_error(error_check, g_info.cmds[i][0]); // 에러 문구 출력은 여기서만
	exit(1);
}


////////////////////////test
void	print_double_array(char **arr);

///////////

int		try_builtin_or_execve_sub(int i, char **envp)
{
	int		path_idx;
	int		path_string_idx;
	char	*tmp;

	path_idx = find_index_of_path_in_env(envp);
	if (path_idx < 0)
		return (CMD_NOT_FOUND);
	path_string_idx = 5;
	// print_double_array(g_info.cmds[i]);
	while (envp[path_idx][path_string_idx] != '\0')
	{
		tmp = try_builtin_or_execve_sub2(&path_string_idx, path_idx, i, envp);
		if (tmp == NULL)
		{
			return (MALLOC_ERROR);
		}
		execve(tmp, g_info.cmds[i], envp);
		// perror("execve");/////////////
		// write(1, " ", 1);//////////////
		// write(1, tmp, ft_strlen(tmp));////////////
		// write(1, "\n ", 2);/////////////////////
		// write(1, g_info.cmds[i][0], ft_strlen(g_info.cmds[i][0]));/////////////
		// write(1, "\n\n", 2);/////////////////////////////////////////////
		free(tmp);
	}
	//디버그
	// write(1, "execve_sub_not_found\n", ft_strlen("execve_sub_not_found\n"));
	return (CMD_NOT_FOUND);
}

// PATH변수에서 path_string_idx에 있는 글자부터 ':' 또는 널문자 나올 때까지 있는 스트링을 동적 할당해서 반환
// ':'을 만났다면 path_string_idx를 ':' 다음 글자로 설정,
// 		널문자를 만났다면 그냥 널문자 자리로 설정해준다.
char	*try_builtin_or_execve_sub2(int *path_string_idx, int path_idx, int i
	, char **envp)
{
	int		end_idx;
	char	*tmp;
	char	*ret;

	end_idx = *path_string_idx;
	while (envp[path_idx][end_idx] != ':' && envp[path_idx][end_idx] != '\0')
		++end_idx;
	tmp = ft_strndup(envp[path_idx] + (*path_string_idx), end_idx - *path_string_idx);
	if (tmp == NULL)
		return (NULL);
	ret = pipe_strjoin(tmp, "/", g_info.cmds[i][0]);
	free(tmp);
	if (ret == NULL)
		return (NULL);
	if (envp[path_idx][end_idx] == ':')
		*path_string_idx = end_idx + 1;
	else
		*path_string_idx = end_idx;
	return (ret);
}

int		find_index_of_path_in_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0) // "PATH="까지 다섯 글자
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
