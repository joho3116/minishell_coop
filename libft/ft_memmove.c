/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:36:59 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 15:52:32 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Segmentation fault occurs when only one of the strings is NULL.
**	If both strings are NULL, segmentation falut error does not occur.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*dst_again;
	const unsigned char		*src_again;

	if (dst == 0 && src == 0)
		return (dst);
	dst_again = dst;
	src_again = src;
	if (dst <= src)
		while (len--)
			*dst_again++ = *src_again++;
	else
		while (len--)
			dst_again[len] = src_again[len];
	return (dst);
}
