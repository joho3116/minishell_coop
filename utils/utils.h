#ifndef UTILS_H
# define UTILS_H

void	safe_free(void **ptr);

void	ft_perror(char *s);
void	print_error(int error_type, char *opt);

t_list	*find_node_at_idx_in_list(t_list *lst, int idx);

#endif
