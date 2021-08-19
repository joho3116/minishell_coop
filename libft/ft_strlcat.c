/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 18:27:14 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 14:39:21 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dst_temp;
	const char	*src_temp;
	size_t		dst_len;
	int			i;

	dst_len = ft_strlen(dst);
	i = dstsize - (int)dst_len;
	if (i <= 0)
		return (dstsize + ft_strlen(src));
	dst_temp = dst + dst_len;
	src_temp = src;
	while (*src_temp)
	{
		if (i != 1)
		{
			*dst_temp++ = *src_temp;
			i--;
		}
		src_temp++;
	}
	*dst_temp = 0;
	return (dst_len + (src_temp - src));
}
