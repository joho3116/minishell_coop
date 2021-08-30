
#include "../includes/parse.h"

t_info g_info;


#include <stdio.h>
#include <string.h>

int main()
{
	char *line;
	char *buf = NULL;

	g_info.lex_head = NULL;
	while (1)
	{
		line = readline("$> ");
		if (strcmp("EOF", line) == 0)
			break ;
		make_string_and_link_node(NORMAL, *line);
		printf(" %s\n", line);
		if (line != NULL)
			free(line);

	}
	make_string_and_link_node(FINAL_CHAR, 'f');
	
	printf("%s\n", g_info.lex_head->data);
}
