/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:38:16 by chanlee           #+#    #+#             */
/*   Updated: 2021/06/30 21:11:17 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Allocates (with malloc(3)) and returns a substring from the string ’s’.
**	The substring begins at index ’start’ and is of maximum size ’len’.
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (len-- && s[start])
	{
		ret[i++] = s[start++];
	}
	ret[i] = 0;
	return (ret);
}
