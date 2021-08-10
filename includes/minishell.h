#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>


# include "../parse/parse.h"
# include "../utils/utils.h"

# define NORMAL 0
# define LEX_FINAL_W_CHAR 1
# define LEX_FINAL_WO_CHAR 2
# define LEX_FOR_FREE 3

# define MALLOC_ERROR -2
# define SYNTAX_ERROR -3

# define IN_REDIR 11
# define OUT_REDIR 12
# define IN_REDIR_LIM 13
# define OUT_REDIR_APP 14
# define PIPE 15
# define NOT_REDIR 16

// list_lex_head는 NULL로 초기화
typedef	struct s_info
{
	t_list			*lex_head;
	char			**envp;
	unsigned int	exit_status;
	char			***cmds;
	t_list			*cmd_redir_lst;
	int				num_of_cmds;
}				t_info;

extern t_info g_info;

#endif