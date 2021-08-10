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

void	testprint_redirec_lst()
{
	int i = 0;
	t_list *idx = g_info.cmd_redir_lst;
	while (idx)
	{
		printf("#%d cmd\n", i);
		t_list *tmp = idx->data;
		// if (tmp = NULL)
			printf("tmp = %p\n", tmp);
		while (tmp)
		{
			printf("\t");
			if (((t_redir_lst_nod*)(tmp->data))->type == IN_REDIR)
				printf("<");
			else if (((t_redir_lst_nod*)(tmp->data))->type == OUT_REDIR)
				printf(">");
			else if (((t_redir_lst_nod*)(tmp->data))->type == IN_REDIR_LIM)
				printf("<<");
			else if (((t_redir_lst_nod*)(tmp->data))->type == OUT_REDIR_APP)
				printf(">>");
			printf(" |%s|\n", ((t_redir_lst_nod*)(tmp->data))->path);
			tmp = tmp->next;
		}
		idx = idx->next;
		++i;
	}

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
		return (error_check);
	error_check = only_alloc_space_for_cmds(&parsecnt);
	if (error_check < 0)
		return (error_check);
	error_check = parse_only_redirection(&parsecnt, g_info.lex_head);
	if (error_check < 0)
		return (error_check);

	testprint_redirec_lst(); // only_alloc과 parse_only 테스트
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
	{
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		return (MALLOC_ERROR);
	}
	nodtmp = ft_lstnew(inttmp); // 동적할당 리턴
	if (nodtmp == NULL)
	{
		free(inttmp);
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
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
	{
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		return (MALLOC_ERROR);
	}
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
		// printf("i = %d : allocated blocks = %d\n\t add = %p\n", i, *(int *)(num_tokens_idx->data) + 1, (*tmp)[i]); // 테스트용
		(*tmp)[i][0] = NULL; // 첫 인덱스를 NULL로 초기화해줘야 나중에 문제 생겨서 free해줄 때도 쓰레기 값을 free하는 문제 방지할 수 있음
		// printf("\t\t(*tmp)[%d][0] = %p\n", i, (*tmp)[i][0]);
		num_tokens_idx = num_tokens_idx->next;
	}
	(*tmp)[i] = NULL;
	// printf("last %dth address = %p\n", i, (*tmp)[i]);
	return (0);
}

int		only_alloc_space_for_cmds_error_return(t_parsetmp *parsecnt, char ****tmp)
{
	int		i;

	ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
	ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
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

int		parse_only_redirection(t_parsetmp *parsecnt, t_list *idx)
{
	int		token_check;
	int		error_check;
	t_list	*head_of_node;

	g_info.cmd_redir_lst = NULL;
	head_of_node = NULL;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{
			if (lst_add_redirec_lst(parsecnt, head_of_node) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			head_of_node = NULL;
		}
		else if (token_check != NOT_REDIR)
		{
			error_check = append_on_redirec_lst_node(parsecnt, &head_of_node, &idx);
			if (error_check < 0)
				return (error_check);
		}
		idx = idx->next;
	}
	if (lst_add_redirec_lst(parsecnt, head_of_node) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0);
}

// 리스트가 다른 리스트의 노드로 들어가는 형식
int		lst_add_redirec_lst(t_parsetmp *parsecnt, t_list *data)
{
	t_list	*nodtmp;

	nodtmp = ft_lstnew((void *)data);
	if (nodtmp == NULL)
	{
		ft_lstclear(&data, &fun_clear_redirec_lst_data); // 넣으려 했던 노드도 동적할당된 리스트이므로 해제
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free); // 커맨드별 토큰 갯수 리스트도 해제
		ft_lstclear(&(g_info.cmd_redir_lst), &fun_clear_redirec_lst); // 커맨드별 리디렉션 리스트도 해제
		ft_lstclear(&(g_info.lex_head), &free); // 토큰 리스트도 해제
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(g_info.cmd_redir_lst), nodtmp);
}

void	fun_clear_redirec_lst(void *head)
{
	t_list	*idx;
	t_list	*tmp;

	if (head == NULL)
		return ;
		// ft_lstclear(&(t_list *)head, &fun_clear_redirec_lst_data);
	idx = head;
	while (idx)
	{
		tmp = idx->next;
		fun_clear_redirec_lst_data(idx->data);
		idx = tmp;
	}
}

void	fun_clear_redirec_lst_data(void *data)
{
	t_redir_lst_nod	*tmp;

	tmp = data;
	free(tmp->path);
	free(tmp);
}

int		append_on_redirec_lst_node(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx)
{
	t_list *i;

	i = *idx;

	if (i->next == NULL || ft_which_redirection_token(i->next->data) != NOT_REDIR)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		ft_lstclear(&(g_info.cmd_redir_lst), &fun_clear_redirec_lst);
		ft_lstclear(&(g_info.lex_head), &free);
		return (SYNTAX_ERROR);
	}

	return (append_on_redirec_lst_node_sub(parsecnt, head_of_node, idx));
}

int		append_on_redirec_lst_node_sub(t_parsetmp *parsecnt, t_list **head_of_node, t_list **idx)
{
	t_redir_lst_nod		*data;
	t_list				*nod;

	data = (t_redir_lst_nod *)malloc(sizeof(t_redir_lst_nod));
	if (data == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		ft_lstclear(&(g_info.cmd_redir_lst), &fun_clear_redirec_lst);
		ft_lstclear(&(g_info.lex_head), &free);
		return (MALLOC_ERROR);
	}
	data->type = ft_which_redirection_token((*idx)->data);
	data->path = ft_strdup((*idx)->next->data);
	if (data->path == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		ft_lstclear(&(g_info.cmd_redir_lst), &fun_clear_redirec_lst);
		ft_lstclear(&(g_info.lex_head), &free);
		free(data);
		return (MALLOC_ERROR);
	}
	nod = (t_list *)malloc(sizeof(t_list));
	if (nod == NULL)
	{
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		ft_lstclear(&(parsecnt->num_of_tokens_in_one_cmd), &free);
		ft_lstclear(&(g_info.cmd_redir_lst), &fun_clear_redirec_lst);
		ft_lstclear(&(g_info.lex_head), &free);
		free(data->path);
		free(data);
		return (MALLOC_ERROR);
	}
	nod->data = data;
	nod->next = NULL;
	ft_lstadd_back(head_of_node, nod);
	(*idx) = (*idx)->next;
	return (0);
}
