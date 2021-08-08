#ifndef PARSE_H
# define PARSE_H

# define NORMAL 0
# define FINAL_W_CHAR 1
# define FINAL_WO_CHAR 2
# define FOR_FREE 3

# define END_LINE 0
# define MALLOC_ERROR -2
# define SYNTAX_ERROR -3

int		tokenize(char *line);
int		tokenize_return_check(int status);

int		at_single_quote(char **line);
int		at_double_quote(char **line);

int		expand_dollar_sign(char **line);

int		at_redirection_char(char **line);
int		at_white_spaces(char **line);


int		expand_exit_status_and_append_string(void);
int		ft_is_in_expansion(char ch);
int		find_env_var_and_mov_ptr(char **line);
int		only_find_env_var(char *start, int len);

int		make_string_and_link_node(int mode, char ch);
int		append_char(char **buf, char ch);

void	free_in_lex(void);

#endif