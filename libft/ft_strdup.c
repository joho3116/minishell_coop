/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:52:25 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/04 03:02:23 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ret;
	size_t	i;

	i = -1;
	len = ft_strlen(s1);
	ret = (char *)malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	while (++i <= len)
	{
		ret[i] = s1[i];
	}
	return (ret);
}
