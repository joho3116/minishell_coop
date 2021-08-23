#include "../includes/minishell.h"

// errno가 셋팅되지 않을 수도 있는 경우에 이 함수로 에러 문구 출력
void print_error(int error_type, char *opt)
{
	if (error_type == MALLOC_ERROR)
	{
		ft_perror(strerror(errno));
	}
	else if (error_type == SYNTAX_ERROR)
	{
		ft_putstr_fd("parse error\n", 2);
	}
	else if (error_type == CMD_NOT_FOUND)
	{
		ft_putstr_fd("cmd not found : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_type == REDIR_INFO_NODE_NOT_FOUND)
	{
		ft_putstr_fd("redirection info not found : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_type == REDIR_INFO_NODE_NULL)
	{
		ft_putstr_fd("redirection info node null : ", 2);
		ft_putstr_fd(opt, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (error_type == READ_ERROR)
	{
		ft_perror(strerror(errno));
	}
	else
	{
		ft_putstr_fd("unknown type error\n", 2);
	}
}
