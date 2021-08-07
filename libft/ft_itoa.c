/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 04:03:46 by chanlee           #+#    #+#             */
/*   Updated: 2021/07/02 15:37:32 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	function 'digit' returns the number of non-null characters
**	in the string which we want to return.
**	It also counts '-' in negative numbers and '0' in integer zero.
*/

static size_t	digit(int n)
{
	size_t	ret;
	size_t	add;

	if (n == -2147483648)
		return (11);
	if (n <= 0)
		add = 1;
	else
		add = 0;
	if (n < 0)
		n = -n;
	ret = 0;
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret + add);
}

static void	ft_itoa_sub(int n, char *ret, int *flag)
{
	int			i;
	long long	temp;

	i = (int)digit(n);
	ret[i--] = 0;
	temp = n;
	while (i >= 0)
	{
		if (temp < 0)
			ret[i--] = ((*flag) *(temp % 10) + '0');
		else
			ret[i--] = (temp % 10) + '0';
		temp /= 10;
	}
	if (*flag < 0)
		ret[0] = '-';
}

char	*ft_itoa(int n)
{
	char		*ret;
	int			flag;

	if (n < 0)
		flag = -1;
	else
		flag = 0;
	ret = (char *)malloc(sizeof(char) * digit(n) + 1);
	if (ret == NULL)
		return (NULL);
	ft_itoa_sub(n, ret, &flag);
	return (ret);
}
