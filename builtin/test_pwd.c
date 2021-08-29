#include "../includes/minishell.h"

int	main()
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}
