#include "../includes/minishell.h"
///////////////////////////테스트용 함수
#include <stdio.h>

void	testprint_num_token(void *data)
{
	printf("|%d|\n", *(int *)data);
}

void	testprint_count_parse(t_parsetmp *parsecnt)
{
	printf("num of cmds = %d\n", parsecnt->num_of_cmds);
	ft_lstiter(parsecnt->num_of_tokens_in_one_cmd, &testprint_num_token);
}




///////////////////////////테스트용 함수 끝
int		parse_all(void)
{
	t_parsetmp	parsecnt;
	int			error_check;

	//t_parsetmp 초기화
	parsecnt.num_of_cmds = 0;
	parsecnt.num_of_tokens_in_one_cmd = NULL;

	error_check = count_parse(&parsecnt, g_info.lex_head);
	if (error_check < 0)
	{
		free_in_parse(&parsecnt);
		return (error_check);
	}
	testprint_count_parse(&parsecnt); // 테스트프린트용
}

// count해줘야 그에 맞게 동적 할당 가능
// idx 매개 변수는 줄 수 줄이기 위한 꼼수
int		count_parse(t_parsetmp *parsecnt, t_list *idx)
{
	int		token_check;
	int		*inttmp;
	void	*nodtmp;
	int		redir_cnt;

	redir_cnt = 0;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			parsecnt->num_of_cmds++;
			if (lst_add_num_of_redir(parsecnt, redir_cnt) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			redir_cnt = 0;
			//////////////////////////////////////// lst_add_num_of_redir()로 뺄 부분
			// inttmp = malloc_int_and_set_num(redir_cnt); // 동적할당 리턴
			// if (inttmp == NULL)
			// 	return (MALLOC_ERROR);
			// nodtmp = ft_lstnew(inttmp); // 동적할당 리턴
			// if (nodtmp == NULL)
			// {
			// 	free(inttmp);
			// 	return (MALLOC_ERROR);
			// }
			// ft_lstadd_back(&(parsecnt->num_of_tokens_in_one_cmd), )
			/////////////////////////////////////////// lst_add_num_of_redir()마지막
		}
		else if (token_check == NOT_REDIR)
			;
		else // >, <, >>, <<리디렉션인 경우 여기로
			redir_cnt++;
		idx = idx->next;
	}
	parsecnt->num_of_cmds++;
	if (lst_add_num_of_redir(parsecnt, redir_cnt) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

// 첫 글자가 '>', '<', '|'인 스트링만 인자로 들어오게 된다.
int		ft_which_redirection_token(char *str)
{
	if (str[0] == '\0' || str[1] == '\0') // 세그폴트 방지용
		return (NOT_REDIR);
	if (str[0] == '>' && str[1] == -1)
		return (OUT_REDIR);
	else if (str[0] == '<' && str[1] == -1)
		return (IN_REDIR);
	else if (str[0] == '|' && str[1] == -1)
		return (PIPE);
	if (str[2] == '\0')
		return (NOT_REDIR); // 세그폴트 방지용
	else if (str[0] == '>' && str[1] == '>' && str[2] == -1)
		return (OUT_REDIR_APP);
	else if (str[0] == '<' && str[1] == '<' && str[2] == -1)
		return (IN_REDIR_LIM);
	else
		return (NOT_REDIR);

}

t_list	*make_int_ptr_node(int *ptr)
{

}

int		*malloc_int_and_set_num(int num)
{
	int *tmp;

	tmp = (int *)malloc(sizeof(int));
	if (tmp == NULL)
		return (NULL);
	*tmp = num;
	return (tmp);
}

void	free_in_parse(t_parsetmp *parsecnt)
{
	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
}

int		lst_add_num_of_redir(t_parsetmp *parsecnt, int redir_cnt)
{
	int		*inttmp;
	t_list	*nodtmp;

	inttmp = malloc_int_and_set_num(redir_cnt); // 동적할당 리턴
	if (inttmp == NULL)
		return (MALLOC_ERROR);
	nodtmp = ft_lstnew(inttmp); // 동적할당 리턴
	if (nodtmp == NULL)
	{
		free(inttmp);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(parsecnt->num_of_tokens_in_one_cmd), nodtmp);
	return (0);
}
