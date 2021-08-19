/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:28:14 by chanlee           #+#    #+#             */
/*   Updated: 2021/06/30 21:10:49 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	ft_strtrim trims the head part of a string before the first character
**	which is not in the string 'set'.
**	It also trims the tail part of a string after the last character
**	which is not in the string 'set'.
*/

/*
**	Function 'head' returns the index of the first character
**	which is not in the string 'set'.
*/

static int	head(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

/*
**	Function 'tail' returns the index of the last character
**	which is not in the string 'set'.
*/

static int	tail(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*ret;
	size_t	i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = head(s1, set);
	end = tail(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	i = 0;
	ret = (char *)malloc(end - start + 2);
	if (ret == NULL)
		return (NULL);
	while (start <= end)
		ret[i++] = s1[start++];
	ret[i] = 0;
	return (ret);
}
