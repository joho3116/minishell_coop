#include "minishell.h"

void	safe_free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(**ptr);
		*ptr = NULL;
	}
}
