#include "../includes/minishell.h"

int	only_alloc_space_for_cmds(t_count_info_in_parse *parsecnt)
{
	int	error_check;

	g_info.cmds = (char ***)malloc(sizeof(char **)
			* (parsecnt->num_of_cmds + 1));
	if (g_info.cmds == NULL)
	{
		ft_perror("parse");
		return (MALLOC_ERROR);
	}
	error_check = only_alloc_space_for_cmds_sub(parsecnt);
	if (error_check == MALLOC_ERROR)
		return (error_check);
	return (0);
}

int	only_alloc_space_for_cmds_sub(t_count_info_in_parse *parsecnt)
{
	int		i;
	t_list	*num_tokens_idx;

	i = -1;
	num_tokens_idx = (t_list *)(parsecnt->num_of_tokens_in_one_cmd);
	while (++i < parsecnt->num_of_cmds)
	{
		g_info.cmds[i] = (char **)malloc(sizeof(char *)
				* (*(int *)(num_tokens_idx->data) + 1));
		if (g_info.cmds[i] == NULL)
			return (MALLOC_ERROR);
		only_alloc_space_for_cmds_sub2(i, *(int *)(num_tokens_idx->data) + 1);
		num_tokens_idx = num_tokens_idx->next;
	}
	g_info.cmds[i] = NULL;
	return (0);
}

void	only_alloc_space_for_cmds_sub2(int i, int num_of_nulls)
{
	int	j;

	j = 0;
	while (j < num_of_nulls)
	{
		g_info.cmds[i][j] = NULL;
		++j;
	}
}
