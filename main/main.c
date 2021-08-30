#include "includes/minishell.h"

t_info	g_info;

void	print_hex(char *line){
	printf("|");
	for (int i = 0; line[i] != '\0'; i++){
		printf("%#.2x ", line[i]);
	}
	printf("|\n");
}

int	is_not_only_white_spaces(char *line)
{
	while(line)
	{
		if (!(ft_isspace(*line)))
			return (1);
		line++;
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		error_check;

	(void)argv;
	error_check = init_minishell_envp(envp);
	if (error_check < 0)
	{
		print_error(error_check, "MALLOC_ERROR");
		exit(1);
	}
	while (argc)
	{
		line = readline("$> ");
		if (!line || is_not_only_white_spaces(line))
			add_history(line);
		error_check = tokenize(line);
		if (error_check < 0)
		{
			ft_lstclear(&g_info.lex_head, &free);
			free(line);
			// continue ;
			exit(1);
		}
		error_check = parse_all();
		if (error_check < 0)
		{
			free_parse_malloc_in_global_var();
			free(line);
			// continue ;
			exit(1);
		}
		// /*
		// **	int run_cmd(void);
		// */
		// // 실행?
		// error_check = run_cmd();
		// if (error_check < 0)
		// {
		// 	free_parse_malloc_in_global_var();
		// 	free(line);
		// 	continue ;
		// }
		free_parse_malloc_in_global_var();
		free(line);
	}
	return (0);
}
