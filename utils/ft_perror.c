#include "../includes/minishell.h"

void	ft_perror(char *s)
{
	ft_putstr_fd(strerror(errno), 2);
}
