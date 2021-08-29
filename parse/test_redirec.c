
#include "../includes/minishell.h"

t_info g_info;


#include <stdio.h>
#include <string.h>

void print_lst(void *data)
{
	printf("|%s|\n", (char *)data);
}

void	print_cmds()
{
	for (int i = 0; g_info.cmds[i] != NULL; i++)
	{
		printf("%d cmd\n", i);
		for (int j = 0; g_info.cmds[i][j] != NULL; j++)
		{
			printf(" |%s|\n", g_info.cmds[i][j]);
		}
	}
}

void	print_redirec()
{
	t_list	*idx = g_info.cmd_redir_lst;
	int	i = 0;
	while (idx)
	{
		printf("%d cmd\n", i++);
		if (idx->data)
		{
			t_list *tmp = idx->data;
			while (tmp)
			{
				t_redir_lst_nod *tmp2 = tmp->data;
				printf(" ");
				char *to;
				if (tmp2->type == IN_REDIR)
					to = "<";
				else if (tmp2->type == OUT_REDIR)
					to = ">";
				else if (tmp2->type == IN_REDIR_LIM)
					to = "<<";
				else if (tmp2->type == OUT_REDIR_APP)
					to = ">>";
				printf("%s : ", to);
				printf("%s\n", tmp2->path);
				tmp = tmp->next;
			}
		}
		idx = idx->next;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	char *line;
	char *buf = NULL;

	init_minishell_envp(envp);
	g_info.lex_head = NULL;
	// g_info.envp = envp;sfs
	g_info.exit_status = 125;
	while (1)
	{
		line = readline("$> ");
		if (strcmp("EXIT", line) == 0)
			break ;

		// printf("%p\n", g_info.lex_head);
		// printf("|%s|\n", (char *)(g_info.lex_head->data));

		// ft_lstiter(g_info.lex_head, &print_lst);
		int	error_check;
		if (line != NULL)
		{
			error_check = tokenize(line);
			if (error_check != 0){
				printf("tokenize: %d\n", error_check);
			}else{
				error_check = parse_all();
				if (error_check != 0){
					printf("parse: %d\n", error_check);
				}else{
					printf("==cmds\n");
					print_cmds(); // for test
					printf("==redirecs\n");
					print_redirec();
				}
			}
			free(line);
			free_parse_malloc_in_global_var();
		}
	}
	// system("leaks a.out > ");
	// printf("%s\n", g_info.lex_head->data);
}
