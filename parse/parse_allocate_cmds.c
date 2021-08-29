#include "../includes/minishell.h"

int	allocate_cmds(t_count_info_in_parse *parsecnt)
{
	t_list	*idx;
	int		i;
	int		cmd_i;
	int		error_check;

	idx = g_info.lex_head;
	i = 0;
	cmd_i = 0;
	while (i < parsecnt->num_of_cmds && idx)
	{
		error_check = allocate_cmds_sub(parsecnt, &idx, &i, &cmd_i);
		if (error_check < 0)
			return (error_check);
		idx = idx->next;
	}
	(g_info.cmds)[i++][cmd_i] = NULL;
	return (0);
}

int	allocate_cmds_sub(t_count_info_in_parse *parsecnt, t_list **idx
	, int *i, int *cmd_i)
{
	int	token_check;

	token_check = ft_which_redirection_token((*idx)->data);
	if (token_check == PIPE)
	{
		(g_info.cmds)[(*i)++][(*cmd_i)] = NULL;
		(*cmd_i) = 0;
	}
	else if (token_check == NOT_REDIR)
	{
		(g_info.cmds)[(*i)][(*cmd_i)] = ft_strdup((char *)((*idx)->data));
		if ((g_info.cmds)[*i][(*cmd_i)++] == NULL)
		{
			ft_perror("parse");
			return (MALLOC_ERROR);
		}
	}
	else
		(*idx) = (*idx)->next;
	return (0);
}

void	free_cmds(void)
{
	int	i;
	int	j;

	i = -1;
	while ((g_info.cmds)[++i] != NULL)
	{
		j = -1;
		while ((g_info.cmds)[i][++j] != NULL)
			free((g_info.cmds)[i][j]);
		free(g_info.cmds[i]);
	}
	free(g_info.cmds);
	g_info.cmds = NULL;
}
