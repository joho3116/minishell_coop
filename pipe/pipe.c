#include "../includes/minishell.h"

int	run_cmd(void)
{
	if (g_info.cmds[1] == NULL && is_builtin(g_info.cmds[1]))
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
	return (!ft_strcmp(g_info.cmds[0], "echo") || !ft_strcmp(g_info.cmds[1], "cd")
		|| !ft_strcmp(g_info.cmds[0], "pwd") || !ft_strcmp(g_info.cmds[0], "export")
		|| !ft_strcmp(g_info.cmds[0], "unset") || ft_strcmp(g_info.cmds[0], "env")
		|| !ft_strcmp(g_info.cmds[0], "exit"));
}

////////////////////////////////////////////////
// pipe.c 컴파일 되게 하기 위해 임시로 넣어놓은 함수 프로토타입부분

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
	if (ft_strcmp(g_info.cmds[i], "echo") == 0)
	{
		return (builtin_echo(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "cd") == 0)
	{
		return (builtin_cd(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "pwd") == 0)
	{
		return (builtin_pwd(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "export") == 0)
	{
		return (builtin_export(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "unset") == 0)
	{
		return (builtin_unset(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "env") == 0)
	{
		return (builtin_env(i));
	}
	else if (ft_strcmp(g_info.cmds[i], "exit") == 0)
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

	// int	last = 9; // 커맨드 갯수
	int idx = -1;

	while (g_info.cmds[++i] != NULL){
		// if (idx == last){
		// 	break ;
		// }
		pipe(pipe1);
		fd = fork();
		if (fd == 0)
		{ // child
		// 공통

			// 기본 input, output 셋팅
			///////////////////////
			if (idx != 0){
				close(pipe0[1]);
				dup2(pipe0[0], 0);
			}

			close(pipe1[0]);
			if (g_info.cmds[i + 1] == NULL){
				close(pipe1[1]);
			}else{
				dup2(pipe1[1], 1);
			}
			////////////////////////



		// input redirection
			inputfd = check_input_redirection();
			if (inputfd < 0)
			{
				ft_perror(g_info.cmds[i]);
				exit(1);
			}
		////////////////////////////

		// output redirectio
			outputfd = check_output_redirection();
			if (outputfd < 0)
			{
				ft_perror(g_info.cmds[i]);
				exit(1);
			}


			if (idx == 2)
			{
				break;
			}
			try_builtin_or_execve(i);
		}
		if (idx != 0){
			close(pipe0[0]);
			close(pipe0[1]);
		}
		copy_pipe_fd(pipe0, pipe1);
		waitpid(fd, &stat, 0);
		++idx;
	}

}

/*
**	void try_builtin_or_execve(int i);
*/
// 빌트인이면 빌트인 함수 실행
// 실행 파일이면 현재 경로부터 PATH까지 붙여서 execve시도
void	try_builtin_or_execve(int i)
{
	if (is_builtin(g_info.cmds[i]))
		run_only_one_cmd(i);
	else
	{
		
	}
}
