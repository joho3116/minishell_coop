#ifndef PIPE_H
# define PIPE_H

int		run_cmd(void);

int		is_builtin(char *str);

///////////////////////////////

int		run_only_one_cmd(int i);


//////////////////////////////

int		run_pipe(void);

void	try_builtin_or_execve(int i);

#endif
