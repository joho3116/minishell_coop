#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h> // S_IRUSR 매크로 위해(norm 위반? 맥에서는 빼도 돌아가니 나중에 빼기)
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdbool.h>


# include "../parse/parse.h"
# include "../utils/utils.h"
# include "../pipe/pipe.h"

# define OUT_REDIR_PERMISSION_BIT (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

# define STDIN_BACKUP_FD 3
# define STDOUT_BACKUP_FD 4

# define NORMAL 0
# define LEX_FINAL_W_CHAR 1
# define LEX_FINAL_WO_CHAR 2
# define LEX_FOR_FREE 3

# define MALLOC_ERROR -2
# define SYNTAX_ERROR -3
# define CMD_NOT_FOUND -4
# define REDIR_INFO_NODE_NOT_FOUND -5
# define REDIR_INFO_NODE_NULL -6
# define READ_ERROR -7
# define OPEN_ERROR -8
# define ERRNO_SET -9

# define IN_REDIR 11
# define OUT_REDIR 12
# define IN_REDIR_LIM 13
# define OUT_REDIR_APP 14
# define PIPE 15
# define NOT_REDIR 16

# define NO_REDIR_FOR_CMD 0

// list_lex_head는 NULL로 초기화
typedef	struct s_info
{
	t_list			*lex_head;
	// ft_lstclear(&(g_info.lex_head), &free);로 해제
	char			**envp;
	// 아마 동적할당으로?
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
