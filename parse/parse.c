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
	error_check = only_alloc_space_for_cmds(&parsecnt);
	// testprint_count_parse(&parsecnt); // 테스트프린트용
}

// count해줘야 그에 맞게 동적 할당 가능
// idx 매개 변수는 줄 수 줄이기 위한 꼼수
int		count_parse(t_parsetmp *parsecnt, t_list *idx)
{
	int		token_check;
	int		*inttmp;
	void	*nodtmp;
	int		args_cnt;

	args_cnt = 0;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			parsecnt->num_of_cmds++;
			if (lst_add_num_of_args(parsecnt, args_cnt) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			args_cnt = 0;
		}
		else // >, <, >>, <<리디렉션 또는 일반 토큰인 경우 여기로
			args_cnt++;
		idx = idx->next;
	}
	parsecnt->num_of_cmds++;
	if (lst_add_num_of_args(parsecnt, args_cnt) == MALLOC_ERROR)
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

// t_list	*make_int_ptr_node(int *ptr)
// {

// }

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

int		lst_add_num_of_args(t_parsetmp *parsecnt, int args_cnt)
{
	int		*inttmp;
	t_list	*nodtmp;

	inttmp = malloc_int_and_set_num(args_cnt); // 동적할당 리턴
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

int		only_alloc_space_for_cmds(t_parsetmp *parsecnt)
{
	char	***tmp;
	int		error_check;

	tmp = (char ***)malloc(sizeof(char **) * (parsecnt->num_of_cmds + 1));
	if (tmp == NULL)
		return (MALLOC_ERROR);
	error_check = only_alloc_space_for_cmds_sub(parsecnt, &tmp);
	if (error_check == MALLOC_ERROR)
		return (error_check);
}

int		only_alloc_space_for_cmds_sub(t_parsetmp *parsecnt, char ****tmp)
{
	int		i;
	t_list	*num_tokens_idx;

	i = -1;
	num_tokens_idx = (t_list *)(parsecnt->num_of_tokens_in_one_cmd);
	while (++i < parsecnt->num_of_cmds)
	{
		(*tmp)[i] = (char **)malloc(sizeof(char *) *
			(*(int *)(num_tokens_idx->data) + 1));
		if ((*tmp)[i] == NULL)
			return (only_alloc_space_for_cmds_error_return(parsecnt, tmp));
		printf("i = %d : allocated blocks = %d\n\t add = %p\n", i, *(int *)(num_tokens_idx->data) + 1, (*tmp)[i]); // 테스트용
		(*tmp)[i][0] = NULL; // 첫 인덱스를 NULL로 초기화해줘야 나중에 문제 생겨서 free해줄 때도 쓰레기 값을 free하는 문제 방지할 수 있음
		printf("\t\t(*tmp)[%d][0] = %p\n", i, (*tmp)[i][0]);
		num_tokens_idx = num_tokens_idx->next;
	}
	(*tmp)[i] = NULL;
	printf("last %dth address = %p\n", i, (*tmp)[i]);
	return (0);
}

int		only_alloc_space_for_cmds_error_return(t_parsetmp *parsecnt, char ****tmp)
{
	int		i;

	i = 0;
	while (i < parsecnt->num_of_cmds && (*tmp)[i] != NULL)
	{
		free((*tmp)[i]);
		++i;
	}
	free(*tmp);
	*tmp = NULL;
	return (MALLOC_ERROR);
}
