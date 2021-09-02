#ifndef UTILS_H
# define UTILS_H

# include <signal.h>
# include <unistd.h>

void	safe_free(void **ptr);

void	ft_perror(char *s);
void	print_error(int error_type, char *opt);

t_list	*find_node_at_idx_in_list(t_list *lst, int idx);

void	sig_handler(int signum);
void	sig_handler_on_main_at_run_cmd(int signum);
#endif
