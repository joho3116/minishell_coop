/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:41:22 by johokyoun         #+#    #+#             */
/*   Updated: 2021/08/23 16:41:33 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int		parse_only_redirection(t_parsetmp *parsecnt, t_list *idx)
{
	int		token_check;
	int		error_check;
	t_list	*head_of_node; // 각 커맨드별 리디렉션 리스트

	g_info.cmd_redir_lst = NULL;
	head_of_node = NULL;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			if (lst_add_redirec_lst(parsecnt, head_of_node) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			head_of_node = NULL;
		}
		else if (token_check != NOT_REDIR) // 리디렉션 토큰인 경우에만 들어오게 됨
		{
			error_check = append_on_redirec_lst_node(parsecnt, &head_of_node, &idx);
			if (error_check < 0)
				return (error_check);
		}
		idx = idx->next;
	}
	if (lst_add_redirec_lst(parsecnt, head_of_node) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

// 리스트가 다른 리스트의 노드로 들어가는 형식
int		lst_add_redirec_lst(t_parsetmp *parsecnt, t_list *data)
{
	t_list	*nodtmp;

	nodtmp = ft_lstnew((void *)data);
	if (nodtmp == NULL)
	{
		ft_lstclear(&data, &fun_clear_redirec_lst_data); // 넣으려 했던 노드도 동적할당된 리스트이므로 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free); // 커맨드별 토큰 갯수 리스트도 해제
		fun_clear_redirec_lst_all();
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(g_info.cmd_redir_lst), nodtmp);
}

void	fun_clear_redirec_lst_all(void)
{
	t_list	*idx;
	t_list	*temp;

	idx = g_info.cmd_redir_lst;
	while (idx)
	{
		temp = idx->next;
		fun_clear_redirec_lst(idx->data);
		free(idx);
		idx = temp;
	}
	g_info.cmd_redir_lst = NULL;
}

void	fun_clear_redirec_lst(void *head) // parse_utils
{
	t_list	*idx;
	t_list	*tmp;

	idx = head;
	while (idx)
	{
		tmp = idx->next;
		fun_clear_redirec_lst_data(idx->data);
		free(idx);
		idx = tmp;
	}
}

void	fun_clear_redirec_lst_data(void *data) // parse_utils
{
	t_redir_lst_nod	*tmp;

	tmp = data;
	free(tmp->path);
	free(tmp);
}

// 리디렉션 토큰인 경우에만 호출됨
int		append_on_redirec_lst_node(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx)
{
	t_list *i;

	i = *idx;

	// 리디렉션 다음에 다른 토큰 없거나 또 리디렉션 토큰인 경우 신택스 에러
	if (i->next == NULL || ft_which_redirection_token(i->next->data) != NOT_REDIR)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		fun_clear_redirec_lst_all();
		ft_lstclear(&(g_info.lex_head), &free);
		return (SYNTAX_ERROR);
	}

	return (append_on_redirec_lst_node_sub(parsecnt, head_of_node, idx));
}

int		append_on_redirec_lst_node_sub(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx)
{
	t_redir_lst_nod		*data;
	t_list				*nod;

	data = (t_redir_lst_nod *)malloc(sizeof(t_redir_lst_nod));
	if (data == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		fun_clear_redirec_lst_all();
		ft_lstclear(&(g_info.lex_head), &free);
		return (MALLOC_ERROR);
	}
	data->type = ft_which_redirection_token((*idx)->data);
	data->path = ft_strdup((*idx)->next->data);
	if (data->path == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		fun_clear_redirec_lst_all();
		ft_lstclear(&(g_info.lex_head), &free);
		free(data);
		return (MALLOC_ERROR);
	}
	nod = (t_list *)malloc(sizeof(t_list));
	if (nod == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		fun_clear_redirec_lst_all();
		ft_lstclear(&(g_info.lex_head), &free);
		free(data->path);
		free(data);
		return (MALLOC_ERROR);
	}
	nod->data = data;
	nod->next = NULL;
	ft_lstadd_back(head_of_node, nod);
	(*idx) = (*idx)->next;
	return (0);
}
