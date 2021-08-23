/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 16:16:18 by johokyoun         #+#    #+#             */
/*   Updated: 2021/08/23 16:40:03 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_parse(t_parsetmp *parsecnt, t_list *idx)
{
	int		token_check;
	int		*inttmp;
	void	*nodtmp;
	int		args_cnt;

	args_cnt = 0;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			parsecnt->num_of_cmds++;
			if (lst_add_num_of_args(parsecnt, args_cnt) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			args_cnt = 0;
		}
		else // >, <, >>, <<리디렉션 또는 일반 토큰인 경우 여기로
			args_cnt++;
		idx = idx->next;
	}
	parsecnt->num_of_cmds++;
	if (lst_add_num_of_args(parsecnt, args_cnt) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

int		ft_which_redirection_token(char *str)
{
	if (str[0] == '\0' || str[1] == '\0') // 세그폴트 방지용
		return (NOT_REDIR);
	if (str[0] == '>' && str[1] == -1)
		return (OUT_REDIR);
	else if (str[0] == '<' && str[1] == -1)
		return (IN_REDIR);
	else if (str[0] == '|' && str[1] == -1)
		return (PIPE);
	if (str[2] == '\0')
		return (NOT_REDIR); // 세그폴트 방지용
	else if (str[0] == '>' && str[1] == '>' && str[2] == -1)
		return (OUT_REDIR_APP);
	else if (str[0] == '<' && str[1] == '<' && str[2] == -1)
		return (IN_REDIR_LIM);
	else
		return (NOT_REDIR);

}

int		lst_add_num_of_args(t_parsetmp *parsecnt, int args_cnt)
{
	int		*inttmp;
	t_list	*nodtmp;

	inttmp = malloc_int_and_set_num(args_cnt); // 동적할당 리턴
	if (inttmp == NULL)
	{
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		return (MALLOC_ERROR);
	}
	nodtmp = ft_lstnew(inttmp); // 동적할당 리턴
	if (nodtmp == NULL)
	{
		free(inttmp);
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(parsecnt->num_of_tokens_in_one_cmd), nodtmp);
	return (0);
}

int	*malloc_int_and_set_num(int num)
{
	int *tmp;

	tmp = (int *)malloc(sizeof(int));
	if (tmp == NULL)
		return (NULL);
	*tmp = num;
	return (tmp);
}
