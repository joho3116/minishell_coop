#include "../includes/minishell.h"

// errno가 셋팅되는 에러는 이거로 에러 출력 가능
void	ft_perror(char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}
