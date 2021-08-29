#ifndef PIPE_H
# define PIPE_H

# define BUF_SIZE 10

int		run_cmd(void);

int		is_builtin(char *str);

///////////////////////////////

int		run_only_one_cmd(int i);
int		run_only_one_cmd_builtin(int i);
int		run_only_one_cmd_not_builtin(int i);


//////////////////////////////
int		num_of_cmd(void);

int		run_pipe(void);

int		restore_stdin_stdout(void);

int		check_input_redirection(int i, int pip[]);

// void	count_input_redirections(int i, int *input_cnt, t_list *node);

int		check_output_redirection(int i, int pip[]);

void	try_builtin_or_execve(int i);

int		try_builtin_or_execve_sub(int i, char **envp);

char	*try_builtin_or_execve_sub2(int *path_string_idx, int path_idx, int i
, char **envp);

int		find_index_of_path_in_env(char **envp);

char	*pipe_strjoin(char *s1, char *s2, char *s3);

#endif
