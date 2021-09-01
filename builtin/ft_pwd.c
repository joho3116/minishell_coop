/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:29:13 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/01 17:26:49 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/minishell.h"

int	ft_pwd(int i)
{
	char	*path;

	if (g_info.cmds[i][1] != NULL)
		return (-1);
	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	free(path);
	return (0);
}
