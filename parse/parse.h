#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

# define NORMAL 0
# define FINAL_CHAR 1
# define FOR_FREE 2

# define END_LINE 0
# define MALLOC_ERROR -2
# define SYNTAX_ERROR -3

int		tokenize(char *line);
int		tokenize_return_check(int status);

int		at_single_quote(char **line);
int		at_double_quote(char **line);
int		at_redirection_char(char **line);
int		at_white_spaces(char **line);

int		make_string_and_link_node(int mode, char ch);
int		append_char(char **buf, char ch);

void	free_in_lex(void);

#endif