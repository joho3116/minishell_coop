/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:16:50 by chanlee           #+#    #+#             */
/*   Updated: 2021/08/07 19:59:16 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*idx;
	t_list	*temp;

	idx = *lst;
	while (idx)
	{
		temp = idx->next;
		ft_lstdelone(idx, del);
		idx = temp;
	}
	*lst = idx;
}
