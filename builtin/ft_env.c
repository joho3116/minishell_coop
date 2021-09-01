/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 22:16:08 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/01 17:21:49 by johokyoun        ###   ########.fr       */
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
        ft_putchar_fd('\n', 1);
        idx = idx->next;
    }
    return (0);
}

t_info g_info;

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		error_check;

    error_check = init_minishell_envp(envp);
	while (1)
	{
		line = readline("$> ");
		error_check = tokenize(line);
		if (error_check < 0)
		{
			print_error(error_check, "");
			ft_lstclear(&g_info.lex_head, &free);
			free(line);
			continue ;
		}
		error_check = parse_all();
		if (error_check < 0)
		{
			/*
			** void free_parse_malloc_in_global_var(void)
			*/
			// 전역변수 내 free할 것들 free
			free_parse_malloc_in_global_var();
			print_error(error_check, "");
			free(line);
			continue ;
		}
		int ret = builtin_env(0);
		printf(" ret = %d\n", ret);
		free_parse_malloc_in_global_var();
		free(line);
	}
}