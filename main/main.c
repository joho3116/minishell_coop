#include "../includes/minishell.h"
#include <stdio.h>

t_info	g_info;

void	print_hex(char *line){
	printf("|");
	for (int i = 0; line[i] != '\0'; i++){
		printf("%#.2x ", line[i]);
	}
	printf("|\n");
}

bool	is_only_white_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (false);
		++line;
	}
	return (true);
}

////////////////////////test
void	print_double_array(char **arr)
{
	for (int i = 0; arr[i] != NULL; i++){
		printf("|%s|\n", arr[i]);
	}
}

///////////

int	main(int argc, char *argv[], char *envp[])
{
	++argc;
	++argv;

	char	*line;
	int		error_check;

	dup2(0, STDIN_BACKUP_FD);
	dup2(1, STDOUT_BACKUP_FD);
	/*
	** int init_minishell(char *envp[]);
	*/
	// 환경변수를 전역변수안에 넣어주기(환경변수 추가 가능해야 하므로 그냥 포인터만 넘기지 않고 새로 동적할당하는 방향으로 구현)
	// 반환값은 에러 체크용
	error_check = init_minishell_envp(envp);


	print_double_array(get_env_list());



	if (error_check < 0)
	{
		/*
		** void print_error(int error_type);
		*/
		// 적절한 에러 문구를 출력해준다.
		print_error(error_check, "init minishell");
		exit(1);
	}

	// signal 셋팅 필요

	while (1)
	{
		// 아직 새 줄에 아무 것도 입력되지 않은 상태에서 readline에 EOF가 들어오면 NULL반환
		line = readline("$> ");


		// readline에서 아무 것도 입력하지 않은 채로 ctrl + d로 eof 보내면 null반환
		// 그러면 쉘 대기 상황에서 ctrl + d받은 경우라 볼 수 있으므로 쉘 종료
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			exit(0);
		}

		/*
		** int is_not_only_white_spaces(char *line);
		*/
		// 들어온 스트링이 화이트 스페이스만 있으면 에러 리턴
		// 화이트 스페이스가 아닌 것이 있으면 0 리턴
		if (is_only_white_spaces(line))
		{
			free(line);
			continue ;
		}
		add_history(line);
		error_check = tokenize(line);
		if (error_check < 0)
		{
			ft_lstclear(&(g_info.lex_head), &free);
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
			free(line);
			continue ;
		}
		/*
		**	int run_cmd(void);
		*/
		// 실행?
		error_check = run_cmd();
		if (error_check < 0)
		{
			free_parse_malloc_in_global_var();
			free(line);
			continue ;
		}
		free_parse_malloc_in_global_var();
		free(line);
	}
}
