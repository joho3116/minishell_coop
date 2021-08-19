/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:53:26 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 15:51:36 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Segmentation fault occurs when only one of the strings is NULL.
**	If both strings are NULL, segmentation falut error does not occur.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_again;
	const unsigned char	*src_again;

	if (dst == 0 && src == 0)
		return (dst);
	dst_again = dst;
	src_again = src;
	while (n--)
	{
		*dst_again++ = *src_again++;
	}
	return (dst);
}
