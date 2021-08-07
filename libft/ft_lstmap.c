/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 22:27:32 by chanlee           #+#    #+#             */
/*   Updated: 2021/08/07 18:28:14 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list	*ret_head;
	t_list	*temp;

	if (!f || !lst)
		return (NULL);
	ret_head = NULL;
	while (lst)
	{
		temp = ft_lstnew(f(lst->data));
		if (temp == NULL)
		{
			ft_lstclear(&ret_head);
			return (NULL);
		}
		ft_lstadd_back(&ret_head, temp);
		lst = lst->next;
	}
	return (ret_head);
}
