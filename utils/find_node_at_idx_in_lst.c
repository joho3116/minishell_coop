#include "../includes/minishell.h"

t_list	*find_node_at_idx_in_list(t_list *lst, int idx)
{
	int		i;
	t_list	*temp;

	temp = lst;
	i = 0;
	while (temp != NULL)
	{
		if (i == idx)
			return (temp);
		temp = temp->next;
		++i;
	}
	return (NULL);
}
