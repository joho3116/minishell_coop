/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:04:12 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 13:38:18 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*idx;

	idx = *lst;
	if (idx == NULL)
	{
		*lst = new;
		return ;
	}
	while (idx->next)
	{
		idx = idx->next;
	}
	idx->next = new;
}
