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

int	init_minishell_envp(char *envp[])
{
	t_list	*idx;

	g_info.env = ft_lstnew(*envp);
	while(*envp++)
	{
		idx = ft_lstnew(*envp);
		ft_lstadd_back(g_info.env, idx);
	}
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_info	info;
	int		error_check;

	/*
	** int init_minishell(char *envp[]);
	*/
	// 환경변수를 전역변수안에 넣어주기(환경변수 추가 가능해야 하므로 그냥 포인터만 넘기지 않고 새로 동적할당하는 방향으로 구현)
	// 반환값은 에러 체크용
	info = malloc(sizeof(t_info));
	error_check = init_minishell_envp(envp);
	if (error_check < 0)
	{
		/*
		** void print_error(int error_type);
		*/
		// 적절한 에러 문구를 출력해준다.
		print_error(error_check, MALLOC_ERROR);
		exit(1);
	}

	while (1)
	{
		// 아직 새 줄에 아무 것도 입력되지 않은 상태에서 readline에 EOF가 들어오면 NULL반환
		line = readline("$> ");

		/*
		** int is_not_only_white_spaces(char *line);
		*/
		// 들어온 스트링이 화이트 스페이스만 있으면 에러 리턴
		// 화이트 스페이스가 아닌 것이 있으면 0 리턴
		if (!line || is_not_only_white_spaces(line))
			add_history(line);
		error_check = tokenize(line);
		if (error_check < 0)
		{
			ft_lstclear(g_info.lex_head, &free);
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
