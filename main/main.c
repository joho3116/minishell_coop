#include "minishell.h"
#include <stdio.h>

t_info	g_info;

void print_hex(char *line){
	printf("|");
	for (int i = 0; line[i] != '\0'; i++){
		printf("%#.2x ", line[i]);
	}
	printf("|\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	int		error_check;
	int		return_value;

	/*
	** int init_minishell(char *envp[]);
	*/
	// 환경변수를 전역변수안에 넣어주기(환경변수 추가 가능해야 하므로 그냥 포인터만 넘기지 않고 새로 동적할당하는 방향으로 구현)
	// 반환값은 에러 체크용
	error_check = init_minishell(envp);
	if (error_check < 0)
	{
		/*
		** void print_error(int error_type);
		*/
		// 적절한 에러 문구를 출력해준다.
		print_error(error_check);
		exit(1);
	}

	/*
	**	1. readline으로 입력받기
	**	2. 히스토리에 더해줄 것이면 더해주기
	**	3. 토큰화하기
	**	4. parse하기
	**	5. 커맨드 실행
	**	6. free하기
	*/
	while (1)
	{
		// 아직 새 줄에 아무 것도 입력되지 않은 상태에서 readline에 EOF가 들어오면 NULL반환
		line = readline("$> ");

		/*
		** int is_not_only_white_spaces(char *line);
		*/
		// 들어온 스트링이 화이트 스페이스만 있으면 에러 리턴
		// 화이트 스페이스가 아닌 것이 있으면 0 리턴
		if (line && is_not_only_white_spaces(line))
			add_history(line);
		error_check = tokenize(line);
		if (error_check < 0)
		{
			print_error_before_run_cmd(error_check);
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
			print_error_before_run_cmd(error_check);
			free(line);
			continue ;
		}
		/*
		**	int run_cmd(void);
		*/
		// 실행?
		g_info.exit_status = run_cmd();
		free_parse_malloc_in_global_var();
		free(line);
	}
}
