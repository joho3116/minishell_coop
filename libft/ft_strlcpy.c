/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 17:47:17 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/03 20:47:40 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (src_len >= dstsize)
	{
		ft_memcpy(dst, src, dstsize - 1);
		dst[dstsize - 1] = 0;
	}
	else
		ft_memcpy(dst, src, src_len + 1);
	return (src_len);
}
