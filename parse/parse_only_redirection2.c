#include "../includes/minishell.h"

int	lst_add_redirec_lst(t_list *data)
{
	t_list	*nodtmp;

	nodtmp = ft_lstnew((void *)data);
	if (nodtmp == NULL)
	{
		ft_perror("parse");
		ft_lstclear(&data, &fun_clear_redirec_lst_data);
		fun_clear_redirec_lst_all();
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

void	fun_clear_redirec_lst(void *head)
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

void	fun_clear_redirec_lst_data(void *data)
{
	t_redir_lst_nod	*tmp;

	tmp = data;
	free(tmp->path);
	free(tmp);
}
