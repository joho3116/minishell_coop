#include "../includes/minishell.h"

void	free_parse_malloc_in_global_var(void)
{
	fun_clear_redirec_lst_all();
	ft_lstclear(&(g_info.lex_head), &free);
	free_cmds();
}

// 최종적으로 거르지 못한 신택스 에러 체크
// 1. g_info.cmd_redir_lst에서 data가 NULL인 것 발견시 신택스 에러(ex. "cmd >" 로 끝난 경우)
int	last_syntax_check(t_count_info_in_parse *parsecnt)
{
	t_list	*idx;
	int		i;

	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
	idx = g_info.cmd_redir_lst;
	i = 0;
	while (idx)
	{
		if (g_info.cmds[i][0] == NULL && idx->data == NULL)
			return (SYNTAX_ERROR);
		idx = idx->next;
		++i;
	}
	return (0);
}

int	parse_all(void)
{
	t_count_info_in_parse	parsecnt;
	int						error_check;

	// t_count_info_in_parse 초기화
	parsecnt.num_of_cmds = 0;
	parsecnt.num_of_tokens_in_one_cmd = NULL;
	error_check = count_parse(&parsecnt, g_info.lex_head); // 동적할당해줄 크기 카운트
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = only_alloc_space_for_cmds(&parsecnt); // 실제로 동적할당
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = parse_only_redirection(&parsecnt, g_info.lex_head); // 리디렉션 정보만 다중 리스트로 만들어주기
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	error_check = allocate_cmds(&parsecnt);
	if (error_check < 0)
		return (free_parsecnt_and_return(error_check, &parsecnt));
	return (last_syntax_check(&parsecnt));
	// testprint_redirec_lst(); // only_alloc과 parse_only 테스트
}

int	free_parsecnt_and_return(int ret, t_count_info_in_parse *parsecnt)
{
	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
	return (ret);
}
