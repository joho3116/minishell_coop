#include "../includes/minishell.h"
#include "../libft/libft.h"


int	main(int argc, char *argv[], char *envp[])
{
	t_list	*idx;
	t_list	*test;
	t_info	all;

	all.env = ft_lstnew(*envp);
	// printf("%s\n", all.env->data);
	test = all.env;
	while (*envp++)
	{
		idx = ft_lstnew(*envp);
		ft_lstadd_back(&(all.env), idx);
		// printf("envp is == %s\n", *envp);
		printf("%s\n", test->data);
		test = test->next;
	}
	return (0);
}
