/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 22:56:03 by chanlee           #+#    #+#             */
/*   Updated: 2021/05/11 20:50:22 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The strnstr() function locates the first occurrence of
**	the null-terminated string needle in the string haystack,
**	where not more than len characters are searched.
**	Characters that appear after a `\0' character are not searched.
**	Since the strnstr() function is a FreeBSD specific API,
**	it should only be used when portability is not a concern.
*/

/*
**	In a while loop in ft_strnstr, the value of 'len' is the number of
**	characters that we search.
**	So, if len is less than 'needle_len', we are not able to find
**	the needle string in a haystack string.
*/

/*
**	If at least one of the strings are null string, strnstr segfaults.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack && len >= needle_len)
	{
		i = 0;
		while (haystack[i] == needle[i] && i < needle_len)
			i++;
		if (i == needle_len)
			return ((char *)haystack);
		len--;
		haystack++;
	}
	return (NULL);
}
