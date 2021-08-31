#include "../includes/minishell.h"

void	print_prompt(void)
{
	printf("%s", getcwd(NULL, 0));
	printf("$\n");
}
// 임시 제작 프롬프트 출력 함수, getcwd 사용법 확실히 더 숙지해야함.

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// \b을 통해 입력되는 시그널 지우고, test 문구 출력, 프롬프트 출력, 이제 동작 구현
	if (signum == SIGQUIT)
		write(1, "\b\b  \b\b", 6);
}

void	sig_handler_on_main_at_run_cmd(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	if (signum == SIGQUIT)
		;
}

// int		main()
// {
// 	signal(SIGINT, sig_handler);
// 	signal(SIGQUIT, sig_handler);
// 	signal(SIGTERM, sig_handler);
// 	while (1)
// 	{
// 		printf("what?\n");
// 		pause();
// 	}
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
