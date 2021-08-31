/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:16:08 by johokyoun         #+#    #+#             */
/*   Updated: 2021/08/31 22:33:01 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_env(int i)
{
    t_list *idx;
    t_env_node *env_data;
    
    if (g_info.cmds[i][1] != NULL)
        return (-1);
    idx = g_info.env;
    while (idx)
    {
        env_data = idx->data;
        ft_putstr_fd(env_data->key, 1);
        ft_putstr_fd("=", 1);
        ft_putstr_fd(env_data->value, 1);
        idx = idx->next;
    }
    return (0);
}