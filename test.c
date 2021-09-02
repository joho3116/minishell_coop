#include <unistd.h>
#include "./libft/libft.h"

char *cat[] = {"/bin/cat", NULL};
int main(int argc, char **argv, char**envp) {

	int pip[2];

	pipe(pip);
	int pid = fork();
	if (pid == 0) {
		close(pip[0]);
		dup2(pip[1], 3);
		// execve(*cat, cat, envp);
		ft_putstr_fd("test\n", 3);
		exit(0);
	}
	else
	{
		close(pip[1]);
		dup2(pip[0], 0);
		execve(*cat, cat, envp);
	}
}
