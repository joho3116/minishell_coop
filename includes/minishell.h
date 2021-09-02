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
# include <signal.h>
# include <stdio.h>

# include "../parse/parse.h"
# include "../utils/utils.h"
# include "../pipe/pipe.h"
# include "../builtin/builtin.h"
# include "../env/env.h"

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
# define HOME_NOT_FOUND -9
# define STD_FD_RESTORE_FAIL -10
# define ERRNO_SET -11


# define IN_REDIR 11
# define OUT_REDIR 12
# define IN_REDIR_LIM 13
# define OUT_REDIR_APP 14
# define PIPE 15
# define NOT_REDIR 16

# define NO_REDIR_FOR_CMD 0

// 폰트 색
//Regular text
# define CC_BLK "\e[0;30m"
# define CC_RED "\e[0;31m"
# define CC_GRN "\e[0;32m"
# define CC_YEL "\e[0;33m"
# define CC_BLU "\e[0;34m"
# define CC_MAG "\e[0;35m"
# define CC_CYN "\e[0;36m"
# define CC_WHT "\e[0;37m"

//Regular bold text
# define CC_BBLK "\e[1;30m"
# define CC_BRED "\e[1;31m"
# define CC_BGRN "\e[1;32m"
# define CC_BYEL "\e[1;33m"
# define CC_BBLU "\e[1;34m"
# define CC_BMAG "\e[1;35m"
# define CC_BCYN "\e[1;36m"
# define CC_BWHT "\e[1;37m"

//Regular underline text
# define CC_UBLK "\e[4;30m"
# define CC_URED "\e[4;31m"
# define CC_UGRN "\e[4;32m"
# define CC_UYEL "\e[4;33m"
# define CC_UBLU "\e[4;34m"
# define CC_UMAG "\e[4;35m"
# define CC_UCYN "\e[4;36m"
# define CC_UWHT "\e[4;37m"

//Regular background
# define CC_BLKB "\e[40m"
# define CC_REDB "\e[41m"
# define CC_GRNB "\e[42m"
# define CC_YELB "\e[43m"
# define CC_BLUB "\e[44m"
# define CC_MAGB "\e[45m"
# define CC_CYNB "\e[46m"
# define CC_WHTB "\e[47m"

//High intensty background
# define CC_BLKHB "\e[0;100m"
# define CC_REDHB "\e[0;101m"
# define CC_GRNHB "\e[0;102m"
# define CC_YELHB "\e[0;103m"
# define CC_BLUHB "\e[0;104m"
# define CC_MAGHB "\e[0;105m"
# define CC_CYNHB "\e[0;106m"
# define CC_WHTHB "\e[0;107m"

//High intensty text
# define CC_HBLK "\e[0;90m"
# define CC_HRED "\e[0;91m"
# define CC_HGRN "\e[0;92m"
# define CC_HYEL "\e[0;93m"
# define CC_HBLU "\e[0;94m"
# define CC_HMAG "\e[0;95m"
# define CC_HCYN "\e[0;96m"
# define CC_HWHT "\e[0;97m"

//Bold high intensity text
# define CC_BHBLK "\e[1;90m"
# define CC_BHRED "\e[1;91m"
# define CC_BHGRN "\e[1;92m"
# define CC_BHYEL "\e[1;93m"
# define CC_BHBLU "\e[1;94m"
# define CC_BHMAG "\e[1;95m"
# define CC_BHCYN "\e[1;96m"
# define CC_BHWHT "\e[1;97m"

//Reset
# define CC_RESET "\e[0m"

// list_lex_head는 NULL로 초기화
typedef	struct s_info
{
	t_list			*lex_head;
	// ft_lstclear(&(g_info.lex_head), &free);로 해제
	t_list			*env;
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
extern const char * const sys_siglist[];
bool	is_only_white_spaces(char *line);


#endif
