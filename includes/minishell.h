#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>


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
	// ft_lstclear(&(g_info.lex_head), &free);로 해제
	t_list			*env;
	// 아마 동적할당으로? -> t_list 형태로 데이터에 키와 밸류 문자열로 삽입, 따로 출력해야할 경우 split을 이용하면 될 듯...?
	unsigned int	exit_status;
	char			***cmds;
	// (char **)까지만 해제
	// (char *)는 lex_head와 겹치니 이중 free하지 않게 주의
	t_list			*cmd_redir_lst;
	// fun_clear_redirec_lst_all();로 free
	int				num_of_cmds;
}				t_info;

extern t_info g_info;

#endif
