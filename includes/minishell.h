#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


// list_lex_head는 NULL로 초기화
typedef	struct s_info
{
	t_list	*lex_head;
}				t_info;

extern t_info g_info;

#endif