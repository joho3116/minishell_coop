
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
		printf(" %s\n", line);
		append_char(&buf, *line);
		if (line != NULL)
			free(line);

	}
	printf("%s\n", buf);
}
