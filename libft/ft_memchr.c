/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:07:27 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 15:58:20 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The memchr() function returns a pointer to the byte where c is located,
**	or NULL if no such byte exists within n bytes.
*/

/*
**	memchr segfaults when s is null string.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ret;

	ret = (unsigned char *)s;
	while (n--)
	{
		if ((unsigned char)*ret == (unsigned char)c)
			return (ret);
		ret++;
	}
	return (NULL);
}
