#include "../includes/minishell.h"

int	parse_only_redirection(t_count_info_in_parse *parsecnt, t_list *idx)
{
	int		token_check;
	int		error_check;
	t_list	*head;

	head = NULL;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			if (lst_add_redirec_lst(parsecnt, head) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			head = NULL;
		}
		else if (token_check != NOT_REDIR)
		{
			error_check = append_on_redirec_lst_node(parsecnt, &head, &idx);
			if (error_check < 0)
				return (error_check);
		}
		idx = idx->next;
	}
	if (lst_add_redirec_lst(parsecnt, head) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

int	append_on_redirec_lst_node(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx)
{
	t_list	*i;

	i = *idx;
	if (i->next == NULL
		|| ft_which_redirection_token(i->next->data) != NOT_REDIR)
	{
		print_error(SYNTAX_ERROR, "parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		return (SYNTAX_ERROR);
	}
	return (append_on_redirec_lst_node_sub(parsecnt, head_of_node, idx));
}

int	append_on_redirec_lst_node_sub(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx)
{
	t_redir_lst_nod		*data;

	data = (t_redir_lst_nod *)malloc(sizeof(t_redir_lst_nod));
	if (data == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		return (MALLOC_ERROR);
	}
	data->type = ft_which_redirection_token((*idx)->data);
	data->path = ft_strdup((*idx)->next->data);
	if (data->path == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		free(data);
		return (MALLOC_ERROR);
	}
	return (append_on_redirec_lst_node_sub2(parsecnt, head_of_node, idx, data));
}

int	append_on_redirec_lst_node_sub2(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx, t_redir_lst_nod *data)
{
	t_list	*nod;

	nod = (t_list *)malloc(sizeof(t_list));
	if (nod == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		fun_clear_redirec_lst_data(data);
		return (MALLOC_ERROR);
	}
	nod->data = data;
	nod->next = NULL;
	ft_lstadd_back(head_of_node, nod);
	(*idx) = (*idx)->next;
	return (0);
}
