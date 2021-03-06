/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hojo <hojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 23:11:02 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/06 15:01:06 by hojo             ###   ########.fr       */
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
    if (tmp == NULL || data == NULL) // Null?????? ??????
    {
        print_error(MALLOC_ERROR, "set only key");
        return (-1);
    }
    data->key = tmp;
    data->value = NULL;
    node = ft_lstnew(data);
    if (node == NULL)
    {
        free(data->key);
        free(data);
        print_error(MALLOC_ERROR, "set only key");
        return (-1);
    }
    ft_lstadd_back(&(g_info.env), node);
    return (0);
}

int builtin_export(int i)
{
	t_list	*tmp;
    char    buf[1024];

    if (g_info.cmds[i][1] == NULL)
        put_env_list();
    else if (g_info.cmds[i][1] != NULL && g_info.cmds[i][2] == NULL)
    {
        if (ft_strchr(g_info.cmds[i][1], '=') == NULL)
        {
            if (find_key_and_return_value(g_info.cmds[i][1]) == NULL)
                if (set_only_key(g_info.cmds[i][1]) < 0)
					return (1);
        }
        else
        {
            ft_strlcpy(buf, g_info.cmds[i][1], 1024);
            buf[ft_key_len(buf)] = '\0';
            if (find_key_and_return_value(buf) == NULL)
			{
                if (set_new_key(g_info.cmds[i][1]) < 0)
					return (1);
            }
			else
			{
				tmp = find_key_and_return_node(buf);
				if (((t_env_node *)(tmp->data))->value != NULL)
					free(((t_env_node *)(tmp->data))->value);
				((t_env_node *)(tmp->data))->value = duplicate_only_value(g_info.cmds[i][1]);
				if (((t_env_node *)(tmp->data))->value == NULL)
					return (1);
			}
        }
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
			// ???????????? ??? free??? ?????? free
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
