#include "../includes/minishell.h"

// 리디렉션 정보만을 추려서 다중 리스트로 만든다.
// 우선 g_info.cmd_redir_lst의 각 노드는 커맨드 하나를 의미.
// 노드 하나의 멤버 data는 또 다른 리스트의 첫번째 node 또는 NULL을 가리킨다.
// 	NULL이 아니라면 가리키고 있는 리스트의 노드 하나는 리디렉션 항목 하나를 의미한다(ex.'> outfile')
// 리디렉션 항목을 의미하게 되는 이 노드의 멤버 data는 (t_redir_lst_nod *)를 가리킨다.
// 	data 안에는 int형태로 된 리디렉션의 타입과 (char *)형태의 리디렉션 경로가 들어있다.
int	parse_only_redirection(t_count_info_in_parse *parsecnt, t_list *idx)
{
	int		token_check;
	int		error_check;
	t_list	*head_of_node; // 각 커맨드별 리디렉션 리스트

	head_of_node = NULL;
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data);
		if (token_check == PIPE)
		{	// 파이프를 만나면 커맨드 하나가 끝난 것이므로 해당 노드를 g_info.cmd_redir_lst에 달아준다.
			if (lst_add_redirec_lst(parsecnt, head_of_node) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			head_of_node = NULL;
		}
		else if (token_check != NOT_REDIR) // 리디렉션 토큰인 경우에만 들어오게 됨
		{	// 한 커맨드 내에서 리디렉션 토큰이 나올 때마다 head_of_node가 가리키는 리스트의 뒤쪽에 리디렉션 정보를 동적할당해서 달아준다.
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

// 리디렉션 토큰인 경우에만 호출됨
int	append_on_redirec_lst_node(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx)
{
	t_list *i;

	i = *idx;
	// 리디렉션 다음에 다른 토큰 없거나 또 리디렉션 토큰인 경우 신택스 에러
	if (i->next == NULL || ft_which_redirection_token(i->next->data) != NOT_REDIR)
	{
		print_error(SYNTAX_ERROR, "parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		return (SYNTAX_ERROR);
	}
	return (append_on_redirec_lst_node_sub(parsecnt, head_of_node, idx));
}

int	append_on_redirec_lst_node_sub(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx)
{
	t_redir_lst_nod		*data;

	data = (t_redir_lst_nod *)malloc(sizeof(t_redir_lst_nod));
	if (data == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		return (MALLOC_ERROR);
	}
	data->type = ft_which_redirection_token((*idx)->data);
	data->path = ft_strdup((*idx)->next->data);
	if (data->path == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		free(data);
		return (MALLOC_ERROR);
	}
	return (append_on_redirec_lst_node_sub2(parsecnt, head_of_node, idx, data));
}

int	append_on_redirec_lst_node_sub2(t_count_info_in_parse *parsecnt
	, t_list **head_of_node, t_list **idx, t_redir_lst_nod *data)
{
	t_list	*nod;

	nod = (t_list *)malloc(sizeof(t_list));
	if (nod == NULL)
	{
		ft_perror("parse");
		ft_lstclear(head_of_node, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
		fun_clear_redirec_lst_data(data);
		return (MALLOC_ERROR);
	}
	nod->data = data;
	nod->next = NULL;
	ft_lstadd_back(head_of_node, nod);
	(*idx) = (*idx)->next; // 리디렉션 토큰인 경우 그 다음 토큰은 리디렉션 경로이므로 토큰 인덱스를 한 칸 더 나가줘야 체크하지 않은 토큰이 된다.
	return (0);
}
