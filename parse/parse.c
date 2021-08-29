#include "../includes/minishell.h"

void	free_parse_malloc_in_global_var(void)
{
	fun_clear_redirec_lst_all();
	ft_lstclear(&(g_info.lex_head), &free);
	free_cmds();
}

int	last_syntax_check(t_count_info_in_parse *parsecnt)
{
	t_list	*idx;
	int		i;

	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
	idx = g_info.cmd_redir_lst;
	i = 0;
	while (idx)
	{
		if (g_info.cmds[i][0] == NULL && idx->data == NULL)
			return (SYNTAX_ERROR);
		idx = idx->next;
		++i;
	}
	return (expand_wildcard());
}

int	parse_all(void)
{
	t_count_info_in_parse	parsecnt;
	int						error_check;

	parsecnt.num_of_cmds = 0;
	parsecnt.num_of_tokens_in_one_cmd = NULL;
	error_check = count_parse(&parsecnt, g_info.lex_head);
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = only_alloc_space_for_cmds(&parsecnt);
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = parse_only_redirection(&parsecnt, g_info.lex_head);
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = allocate_cmds(&parsecnt);
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	return (last_syntax_check(&parsecnt));
}

int	free_parsecnt_and_return(int ret, t_count_info_in_parse *parsecnt)
{
	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
	return (ret);
}

int	expand_wildcard(void)
{
	int	i;
	int	j;
	int	error_check;

	error_check = 0;
	i = -1;
	while (g_info.cmds[++i] != NULL)
	{
		j = -1;
		while (g_info.cmds[i][++j] != NULL)
		{
			if (is_wildcard(g_info.cmds[i][j]))
			{
				error_check = reallocate_args(i, j);
				if (error_check < 0)
					return (error_check);
				j = -1;
			}
		}
	}
	return (0);
}

int	is_wildcard(char *str)
{
	if (*str == '-')
		return (0);
	while (*str)
	{
		if (*str == '*')
			return (1);
		++str;
	}
	return (0);
}

int	reallocate_args(int i, int j)
{
	char	**tmp;
	DIR*	dir_ptr;

	tmp = g_info.cmds[i];
	dir_ptr = opendir(dir_to_open(g_info.cmds[i][j]));
	if (dir_ptr )
}

char	*dir_to_open(char *arg)
{

}
