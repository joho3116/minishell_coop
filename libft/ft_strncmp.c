/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 23:43:55 by chanlee           #+#    #+#             */
/*   Updated: 2021/06/30 21:09:27 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n && ((unsigned char *)s1)[i]
	&& ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
		i++;
	if (i == n)
		return (0);
	return ((int)((unsigned char *)s1)[i] - (int)((unsigned char *)s2)[i]);
}
