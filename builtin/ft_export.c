/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:11:02 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/03 08:17:29 by johokyoun        ###   ########.fr       */
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
    char    **ret; 
    char    **tmps_str;  
    int i;

    i = 0;
    idx = g_info.env;
    ret = get_env_list_with_quotation();
    tmps_str = ret;
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

int set_only_key(char *key)
{
    char *tmp;
    t_env_node *data;
    t_list  *node;
    
    tmp = ft_strdup(key);
    data = (t_env_node *)malloc(sizeof(t_env_node));
    if (tmp == NULL || data == NULL)
    {
        print_error(MALLOC_ERROR, "set only key");
        return (-1);
    }
    data->key = tmp;
    data->value = NULL;
    tmp = NULL;
    node = ft_lstnew(data);
    if (node == NULL)
    {
        free(data->key);
        free(data->value);
        free(data);
        print_error(MALLOC_ERROR, "set only key");
        return (-1);
    }
    ft_lstadd_back(&(g_info.env), node);
    return (0);
}

int builtin_export(int i)
{
    if (g_info.cmds[i][1] == NULL)
        put_env_list();
    else if (g_info.cmds[i][1] != NULL && g_info.cmds[i][2] == NULL)
    {
        if (ft_strchr(g_info.cmds[i][1], '=') == NULL)
        {
            set_only_key(g_info.cmds[i][1]);
            t_list *tmp;
            t_env_node *ret;
            tmp = g_info.env;
            while (tmp->next != NULL)
                tmp = tmp->next;
            ret = tmp->data;
            ft_putstr_fd(ret->key, 1);
        }
        else
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