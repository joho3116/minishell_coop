
#include "../includes/minishell.h"

t_info g_info;


#include <stdio.h>
#include <string.h>

void print_lst(void *data)
{
	printf("|%s|\n", (char *)data);
}

// int	init_minishell_envp(char *envp[])
// {
// 	t_list	*idx;

// 	g_info.env = ft_lstnew(*envp);
// 	while(*envp++)
// 	{
// 		idx = ft_lstnew(*envp);
// 		ft_lstadd_back(&(g_info.env), idx);
// 	}
// 	return (1);
// }

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	char *buf = NULL;

	g_info.lex_head = NULL;
	init_minishell_envp(envp);
	g_info.exit_status = 125;
	while (1)
	{
		line = readline("$> ");
		if (strcmp("EOF", line) == 0)
			break ;
		tokenize(line);

		// printf("%p\n", g_info.lex_head);
		// printf("|%s|\n", (char *)(g_info.lex_head->data));

		ft_lstiter(g_info.lex_head, &print_lst);
		if (line != NULL)
			free(line);
		ft_lstclear(&(g_info.lex_head), &free);

	}

	// printf("%s\n", g_info.lex_head->data);
}
