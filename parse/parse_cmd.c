/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:08:11 by johokyoun         #+#    #+#             */
/*   Updated: 2021/08/23 16:31:02 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		only_alloc_space_for_cmds(t_parsetmp *parsecnt)
{
	char	***tmp;
	int		error_check;

	tmp = (char ***)malloc(sizeof(char **) * (parsecnt->num_of_cmds + 1));
	if (tmp == NULL)
	{
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		return (MALLOC_ERROR);
	}
	error_check = only_alloc_space_for_cmds_sub(parsecnt, &tmp);
	if (error_check == MALLOC_ERROR)
		return (error_check);
}

int		only_alloc_space_for_cmds_sub(t_parsetmp *parsecnt, char ****tmp)
{
	int		i;
	t_list	*num_tokens_idx;

	i = -1;
	num_tokens_idx = (t_list *)(parsecnt->num_of_tokens_in_one_cmd);
	while (++i < parsecnt->num_of_cmds)
	{
		(*tmp)[i] = (char **)malloc(sizeof(char *) *
			(*(int *)(num_tokens_idx->data) + 1));
		if ((*tmp)[i] == NULL)
			return (only_alloc_space_for_cmds_error_return(parsecnt, tmp));
		// printf("i = %d : allocated blocks = %d\n\t add = %p\n", i, *(int *)(num_tokens_idx->data) + 1, (*tmp)[i]); // 테스트용
		(*tmp)[i][0] = NULL; // 첫 인덱스를 NULL로 초기화해줘야 나중에 문제 생겨서 free해줄 때도 쓰레기 값을 free하는 문제 방지할 수 있음
		// printf("\t\t(*tmp)[%d][0] = %p\n", i, (*tmp)[i][0]);
		num_tokens_idx = num_tokens_idx->next;
	}
	(*tmp)[i] = NULL;
	g_info.cmds = (*tmp);
	// printf("last %dth address = %p\n", i, (*tmp)[i]);
	return (0);
}

int		only_alloc_space_for_cmds_error_return(t_parsetmp *parsecnt, char ****tmp)
{
	int		i;

	ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
	i = 0;
	while (i < parsecnt->num_of_cmds && (*tmp)[i] != NULL)
	{
		free((*tmp)[i]);
		++i;
	}
	free(*tmp);
	*tmp = NULL;
	return (MALLOC_ERROR);
}

int	allocate_cmds(t_parsetmp *parsecnt)
{
	int		token_check;
	t_list	*idx;
	int		i;
	int		cmd_i;

	idx = g_info.lex_head;
	i = 0;
	cmd_i = 0;
	while (i < parsecnt->num_of_cmds && idx)
	{
		token_check = ft_which_redirection_token(idx->data);
		if (token_check == PIPE)
		{
			(g_info.cmds)[i++][cmd_i] = NULL;
			cmd_i = 0;
		}
		else if (token_check == NOT_REDIR) // 일반 토큰
		{
			(g_info.cmds)[i][cmd_i++] = (char *)(idx->data);
		}
		else // 리디렉션 토큰(그냥 넘어가면 됨; else문 삭제해도 될듯)
		{
			idx = idx->next;
		}
		idx = idx->next;
	}
	(g_info.cmds)[i++][cmd_i] = NULL;
	(g_info.cmds)[i] = NULL;
	return (0);
}

// char **까지만 해제 char *는 lex해제할 때 해제됨
void	free_cmds(void)
{
	int	i;

	i = -1;
	while ((g_info.cmds)[++i] != NULL)
	{
		free((g_info.cmds)[i]);
	}
	free(g_info.cmds);
	g_info.cmds = NULL;
}
