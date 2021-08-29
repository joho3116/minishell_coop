#include "../includes/minishell.h"

int	builtin_echo(int i)
{
	bool	flag_new_line;
	int		idx;

	flag_new_line = true;
	idx = 0;
	if (g_info.cmds[i][1] != NULL && ft_strcmp(g_info.cmds[i][1], "-n") == 0)
	{
		flag_new_line = false;
		idx = 1;
	}
	while (g_info.cmds[i][++idx] != NULL)
	{
		// ft_putstr_fd(g_info.cmds[i][idx], STDOUT_BACKUP_FD);
		ft_putstr_fd(g_info.cmds[i][idx], 1);
		if (g_info.cmds[i][idx + 1] != NULL){
			ft_putstr_fd(" ", 1);
			// ft_putstr_fd(" ", STDOUT_BACKUP_FD);

		}
	}
	if (flag_new_line == true)
		ft_putstr_fd("\n", 1);
	return (0);
}


// // 테스트 메인
// // 커맨드에는 echo 테스트만 가능(다른 것 테스트하면 세그폴트 떠도 이상하지 않음)
// #include <stdio.h>

// t_info	g_info;


// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	*line;
// 	int		error_check;

// 	while (1)
// 	{
// 		// 아직 새 줄에 아무 것도 입력되지 않은 상태에서 readline에 EOF가 들어오면 NULL반환
// 		line = readline("$> ");

// 		/*
// 		** int is_not_only_white_spaces(char *line);
// 		*/
// 		// 들어온 스트링이 화이트 스페이스만 있으면 에러 리턴
// 		// 화이트 스페이스가 아닌 것이 있으면 0 리턴
// 		// if (!line || is_not_only_white_spaces(line))
// 		// 	add_history(line);
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
// 		int ret = builtin_echo(0);
// 		// printf(" ret = %d\n", ret);
// 		free_parse_malloc_in_global_var();
// 		free(line);
// 	}
// }
