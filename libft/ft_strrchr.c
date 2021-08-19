/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:37:17 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 15:00:57 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The strrchr() function is identical to strchr(),
**	except it locates the last occurrence of c.
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*ret;
	char	*idx;

	ret = NULL;
	idx = (char *)s;
	while (*idx)
	{
		if (*idx++ == (char)c)
			ret = idx - 1;
	}
	if ((char)c == 0)
		return (idx);
	else
		return (ret);
}
