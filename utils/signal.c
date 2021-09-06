#include "../includes/minishell.h"

void	print_prompt(void)
{
	// ft_putstr_fd(getcwd(NULL, 0), 1);
	ft_putstr_fd("$> ", 1);
}
// 임시 제작 프롬프트 출력 함수, getcwd 사용법 확실히 더 숙지해야함.

void	sig_handler(int signum)
{
	pid_t	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{
			ft_putstr_fd("\b\b  \b\b\n", 1);
			print_prompt();
			rl_on_new_line();
			rl_replace_line("" ,0);
			rl_redisplay();
		}
		else
			ft_putchar_fd('\n', 1);
	}
	else if (signum == SIGQUIT)
	{
		if (pid == -1)
			ft_putstr_fd("\b\b  \b\b", 1);
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
	// // if (signum == SIGTERM)
	// {
	// 	printf("test: SIGTERM\n");
	// 	usleep(600);
	// }
}

// int		main()
// {
// 	// printf("pid = %d\n", getpid());
// 	signal(SIGINT, sig_handler);
// 	// signal(SIGQUIT, sig_handler);
// 	// signal(SIGTERM, sig_handler);
// 	while (1)
// 	{
// 		char *line = readline("$> ");
// 		if (line)
// 			printf("|%s|\n", line);
// 	}
// 	return (0);
// }


// - SIGINT (Ctrl - C)
//     - Interrupt 신호, 프로세스 실행을 중지시키고, 종료시키는 역할
//     - 프롬프트를 다시 띄워야한다.
// - SIGQUIT (Ctrl - \)
//     - 프로세스를 종료시킨 뒤, 코어를 덤프하는 역할
//     - 코어덤프 : 프로그램이 비정상적으로 종료되었을 때, 작동 중이던 메모리 상태를 기록한 파일
// - SIGTERM (Ctrl - D)
//     - Terminate 신호, 프로세스를 정상 종료시킴
//     - stdin에 EOF를 등록, 쉘에 더 이상 명령을 입력하지 않겠다는 의미
//     - 프로세스의 할 일을 마치고 터미널 종료
