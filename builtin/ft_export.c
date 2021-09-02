/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanlee <chanlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:11:02 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/02 15:55:51 by chanlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char    **ascending_env_key(t_list *idx, char **ret)
{
    int idx_size;
    int i;
    int step;
    char    **tmps_str;
    char    *tmp_str;

    i = -1;
    tmps_str = ret;
    idx_size = ft_lstsize(idx);
    while (++i < idx_size - 1)
    {
        step = -1;
        while (++step < idx_size - 1 - i)
        {
            if (ft_strcmp(tmps_str[step], tmps_str[step + 1]) > 0)
            {
                tmp_str = tmps_str[step];
                tmps_str[step] = tmps_str[step + 1];
                tmps_str[step + 1] = tmp_str;
            }
        }
    }
    return (tmps_str);
}

int put_env_list()
{
    t_list *idx;
    t_env_node *env_data;
    char    **ret;
    char    **tmps_str;
    int i;

    i = 0;
    idx = g_info.env;
    env_data = idx->data;
    ret = get_env_list_with_quotation();
    tmps_str = ascending_env_key(idx, ret);
    while (*tmps_str)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putstr_fd(*tmps_str++, 1);
        ft_putchar_fd('\n', 1);
    }
    free_envp_list(ret);
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

// t_info g_info;

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*line;
// 	int		error_check;

//     error_check = init_minishell_envp(envp);
// 	while (1)
// 	{
// 		line = readline("$> ");
// 		error_check = tokenize(line);
// 		if (error_check < 0)
// 		{
// 			print_error(error_check, "");
// 			ft_lstclear(&g_info.lex_head, &free);
// 			free(line);
// 			continue ;
// 		}
// 		error_check = parse_all();
// 		if (error_check < 0)
// 		{
// 			/*
// 			** void free_parse_malloc_in_global_var(void)
// 			*/
// 			// 전역변수 내 free할 것들 free
// 			free_parse_malloc_in_global_var();
// 			print_error(error_check, "");
// 			free(line);
// 			continue ;
// 		}
// 		int ret = builtin_export(0);
// 		printf(" ret = %d\n", ret);
// 		free_parse_malloc_in_global_var();
// 		free(line);
// 	}
// }
