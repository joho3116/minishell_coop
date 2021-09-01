/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johokyoun <johokyoun@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 15:29:29 by johokyoun         #+#    #+#             */
/*   Updated: 2021/09/01 17:25:42 by johokyoun        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int builtin_unset(int i)
{
    if (g_info.cmds[i][1] == NULL)
        return (-1);
    if (g_info.cmds[i][1] && g_info.cmds[i][2] == NULL)
        find_key_and_unset(g_info.cmds[i][1]);
    return (0);
}

t_info g_info;

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
// 		int ret = builtin_unset(0);
//         ret = builtin_export(0);
// 		printf(" ret = %d\n", ret);
// 		free_parse_malloc_in_global_var();
// 		free(line);
// 	}
// }