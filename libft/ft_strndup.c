/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 16:19:56 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/14 16:50:58 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int n)
{
	int		len;
	char	*ret;
	int		i;

	i = -1;
	len = ft_strlen(s1);
	if (n <= len)
		len = n;
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	while (++i < len)
		ret[i] = s1[i];
	ret[i] = 0;
	return (ret);
}
