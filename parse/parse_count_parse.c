#include "../includes/minishell.h"

int	count_parse(t_count_info_in_parse *parsecnt, t_list *idx)
{
	int		token_check;
	int		*inttmp;
	void	*nodtmp;
	int		token_cnt;

	token_cnt = 0;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			parsecnt->num_of_cmds++;
			if (lst_add_num_of_tokens(parsecnt, token_cnt) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			token_cnt = 0;
		}
		else
			token_cnt++;
		idx = idx->next;
	}
	parsecnt->num_of_cmds++;
	if (lst_add_num_of_tokens(parsecnt, token_cnt) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

int	ft_which_redirection_token(char *str)
{
	if (str[0] == '\0' || str[1] == '\0')
		return (NOT_REDIR);
	if (str[0] == '>' && str[1] == -1)
		return (OUT_REDIR);
	else if (str[0] == '<' && str[1] == -1)
		return (IN_REDIR);
	else if (str[0] == '|' && str[1] == -1)
		return (PIPE);
	if (str[2] == '\0')
		return (NOT_REDIR);
	else if (str[0] == '>' && str[1] == '>' && str[2] == -1)
		return (OUT_REDIR_APP);
	else if (str[0] == '<' && str[1] == '<' && str[2] == -1)
		return (IN_REDIR_LIM);
	else
		return (NOT_REDIR);
}

int	lst_add_num_of_tokens(t_count_info_in_parse *parsecnt, int args_cnt)
{
	int		*inttmp;
	t_list	*nodtmp;

	inttmp = malloc_int_and_set_num(args_cnt);
	if (inttmp == NULL)
	{
		ft_perror("parse");
		return (MALLOC_ERROR);
	}
	nodtmp = ft_lstnew(inttmp);
	if (nodtmp == NULL)
	{
		ft_perror("parse");
		free(inttmp);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(parsecnt->num_of_tokens_in_one_cmd), nodtmp);
	return (0);
}

int	*malloc_int_and_set_num(int num)
{
	int	*tmp;

	tmp = (int *)malloc(sizeof(int));
	if (tmp == NULL)
		return (NULL);
	*tmp = num;
	return (tmp);
}
