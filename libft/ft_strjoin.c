/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:21:29 by chanlee           #+#    #+#             */
/*   Updated: 2021/06/30 21:09:13 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*ret;
	size_t	i;
	size_t	s1len;

	s1len = ft_strlen(s1);
	total_len = s1len + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (total_len + 1));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	i = -1;
	while (s2[++i])
		ret[s1len + i] = s2[i];
	ret[s1len + i] = 0;
	return (ret);
}
