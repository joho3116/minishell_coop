#include "../includes/minishell.h"

// 리스트가 다른 리스트의 노드로 들어가는 형식
int	lst_add_redirec_lst(t_count_info_in_parse *parsecnt, t_list *data)
{
	t_list	*nodtmp;

	nodtmp = ft_lstnew((void *)data);
	if (nodtmp == NULL)
	{
		ft_perror("parse");
		ft_lstclear(&data, &fun_clear_redirec_lst_data); // 넣으려 했던 노드도 동적할당된 리스트이므로 해제
		fun_clear_redirec_lst_all(); // 이미 만들고 있던 리디렉션 리스트도 해제
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(g_info.cmd_redir_lst), nodtmp);
	return (0);
}

void	fun_clear_redirec_lst_all(void)
{
	t_list	*idx;
	t_list	*temp;

	idx = g_info.cmd_redir_lst;
	while (idx)
	{
		temp = idx->next;
		fun_clear_redirec_lst(idx->data);
		free(idx);
		idx = temp;
	}
	g_info.cmd_redir_lst = NULL;
}

void	fun_clear_redirec_lst(void *head) // parse_utils
{
	t_list	*idx;
	t_list	*tmp;

	idx = head;
	while (idx)
	{
		tmp = idx->next;
		fun_clear_redirec_lst_data(idx->data);
		free(idx);
		idx = tmp;
	}
}

// 리디렉션 항목 한 개를 의미하는 노드의 멤버인 data내에 동적할당된 요소를 전부 해제
void	fun_clear_redirec_lst_data(void *data) // parse_utils
{
	t_redir_lst_nod	*tmp;

	tmp = data;
	free(tmp->path);
	free(tmp);
}
