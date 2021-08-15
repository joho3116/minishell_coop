#ifndef PARSE_H
# define PARSE_H



typedef struct s_list t_list;

typedef struct s_parsetmp
{
	int		num_of_cmds;
	t_list	*num_of_tokens_in_one_cmd;
}				t_parsetmp;

typedef struct s_redir_lst_nod
{
	int		type;
	char	*path;
}				t_redir_lst_nod;

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

/////////////////////////////////

int		parse_all(void);

int		count_parse(t_parsetmp *parsecnt, t_list *idx);

int		ft_which_redirection_token(char *str);

// t_list	*make_int_ptr_node(int *ptr);

int		*malloc_int_and_set_num(int num);

void	free_in_parse(t_parsetmp *parsecnt);

int		lst_add_num_of_args(t_parsetmp *parsecnt, int args_cnt);

int		only_alloc_space_for_cmds(t_parsetmp *parsecnt);

int		only_alloc_space_for_cmds_sub(t_parsetmp *parsecnt, char ****tmp);

int		only_alloc_space_for_cmds_error_return(t_parsetmp *parsecnt, char ****tmp);

int		parse_only_redirection(t_parsetmp *parsecnt, t_list *idx);

int		lst_add_redirec_lst(t_parsetmp *parsecnt, t_list *data);

void	fun_clear_redirec_lst(void *head);

void	fun_clear_redirec_lst_data(void *data);

int		append_on_redirec_lst_node(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx);

int		append_on_redirec_lst_node_sub(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx);


int		allocate_cmds(t_parsetmp *parsecnt);

#endif
