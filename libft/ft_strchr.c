/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:19:52 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/05 14:36:14 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**    The strchr() function locates the first occurrence of c
**	(converted to a char) in the string pointed to by s.
**	The terminating null character is considered to be part of the string;
**	therefore if c is `\0', the functions locate the terminating `\0'.
**
**	The function return a pointer to the located character,
**	or NULL if the character does not appear in the string.
*/

char	*ft_strchr(const char *s, int c)
{
	char	*ret;

	ret = (char *)s;
	while (*ret)
	{
		if (*ret++ == (char)c)
			return (--ret);
	}
	if ((char)c == 0)
		return (ret);
	else
		return (NULL);
}
