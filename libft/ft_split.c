/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 03:31:06 by chanlee           #+#    #+#             */
/*   Updated: 2021/06/30 21:08:18 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count(char *str, char c)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while ((str[i] == c) && str[i])
			i++;
		if (!(str[i] == c) && str[i])
			cnt++;
		while (!(str[i] == c) && str[i])
			i++;
		if (!str[i])
			break ;
	}
	return (cnt);
}

static void	assign(char *ptr, char *str, int i, int leng)
{
	int	start;
	int	idx;

	idx = 0;
	start = i - leng;
	while (idx < leng)
		ptr[idx++] = str[start++];
	ptr[idx] = 0;
}

/*
**	i's value is converted to the index where null character or char c appears.
**	part_lengh returns the length of string between char c (or null character).
*/

static size_t	part_length(size_t *i, char const *s, char c)
{
	size_t	leng;
	size_t	idx;

	idx = *i;
	leng = 0;
	while ((s[idx] == c) && s[idx])
		idx++;
	while (!(s[idx] == c) && s[idx])
	{
		leng++;
		idx++;
	}
	*i = idx;
	return (leng);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	leng;
	int		array_i;

	ret = (char **)malloc(sizeof(char *) * (count((char *)s, c) + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	array_i = 0;
	while (array_i < (int)count((char *)s, c))
	{
		leng = part_length(&i, s, c);
		ret[array_i] = (char *)malloc(sizeof(char) * (leng + 1));
		if (ret[array_i] == 0)
		{
			while (--array_i >= 0)
				free(ret[array_i]);
			free(ret);
			return (NULL);
		}
		assign(ret[array_i++], (char *)s, i, leng);
	}
	ret[array_i] = NULL;
	return (ret);
}
