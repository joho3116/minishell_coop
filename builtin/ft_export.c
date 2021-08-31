/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:11:02 by johokyoun         #+#    #+#             */
/*   Updated: 2021/08/31 22:17:01 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ascending_env_key(t_list *idx, t_env_node *env_data)
{ 
    t_list *tmp_idx;
    t_env_node *tmp_env;
    int idx_size;
    int i;
    int step;

    i = 0;
    step = 0;
    tmp_idx = idx;
    idx_size = ft_lstsize(idx);
    while (i++ < idx_size - 1)
    {
        while (step++ < idx_size - 1)
        tmp_env = tmp_idx->data;
        if (ft_strcmp())
    }

}

int put_env_list()
{
    t_list *idx;
    t_env_node *env_data;
    
    idx = g_info.env;
    env_data = idx->data;
    ascending_env_key(idx, env_data);
    while (idx)
    {
        // env_data = idx->data;
        // ft_putstr_fd("declare -x ", 1);
        // ft_putstr_fd(env_data->key, 1);
        // ft_putstr_fd("=\"", 1);
        // ft_putstr_fd(env_data->value, 1);
        // ft_putstr_fd("\"\n", 1);
        // idx = idx->next;
    }
    return(0);
}

int builtin_export(int i)
{
    if (g_info.cmds[i][1] == NULL)
        put_env_list();
    else if (g_info.cmds[i][1] != NULL && g_info.cmds[i][2] == NULL)
    {
        if (ft_strchr(g_info.cmds[i][1], '=') == NULL)
            return (-1);
        set_new_key(g_info.cmds[i][1]);
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
		int ret = builtin_export(0);
		printf(" ret = %d\n", ret);
		free_parse_malloc_in_global_var();
		free(line);
	}
}