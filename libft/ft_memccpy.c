/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 15:24:20 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 13:58:25 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	memccpy copies until character c appears.
**	A pointer to the byte after the copy of 'c' in the string dst is returned.
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst_ret;
	const unsigned char	*src_again;
	size_t				i;

	dst_ret = dst;
	src_again = src;
	i = 0;
	while (i < n)
	{
		dst_ret[i] = src_again[i];
		if (src_again[i] == (unsigned char)c)
			return (dst_ret + i + 1);
		i++;
	}
	return (NULL);
}
