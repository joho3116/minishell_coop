
#include "../includes/minishell.h"

t_info g_info;


#include <stdio.h>
#include <string.h>

void print_lst(void *data)
{
	printf("|%s|\n", (char *)data);
}

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	char *buf = NULL;

	g_info.lex_head = NULL;
	g_info.envp = envp;
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
