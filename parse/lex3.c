#include "../includes/minishell.h"

int	expand_dollar_sign(char **line)
{
	++(*line);
	if (**line == '?')
		return (expand_exit_status_and_append_string());
	else if (ft_isdigit(**line))
		return (0);
	else if (ft_isalpha(**line))
		return (find_env_var_and_mov_ptr(line));
	else if (ft_isspace(**line))
		return (make_string_and_link_node(NORMAL, '$'));
	else
		return (0);
}

int	expand_exit_status_and_append_string(void)
{
	int		error_check;
	char	*ascii_num;
	int		idx;

	if (g_info.exit_status == 0)
	{
		error_check = make_string_and_link_node(NORMAL, '0');
		return (error_check);
	}
	ascii_num = ft_itoa(g_info.exit_status);
	if (ascii_num == NULL)
	{
		ft_perror("lex");
		return (MALLOC_ERROR);
	}
	idx = -1;
	while (ascii_num[++idx] != 0)
	{
		error_check = make_string_and_link_node(NORMAL, ascii_num[idx]);
		if (error_check < 0)
			break ;
	}
	safe_free((void **)&ascii_num);
	return (error_check);
}

int	ft_is_in_expansion(char ch)
{
	return (ft_isalpha(ch) || ft_isdigit(ch));
}

int	find_env_var_and_mov_ptr(char **line)
{
	char	*start;
	int		len;

	start = *line;
	while (ft_is_in_expansion(**line))
		(*line)++;
	len = ((*line)--) - start;
	return (only_find_env_var(start, len));
}

int	only_find_env_var(char *start, int len)
{
	char	*key_buf;
	char	*value;
	int		error_check;

	key_buf = ft_strndup(start, len);
	if (key_buf == NULL)
	{
		ft_perror("lex");
		return (MALLOC_ERROR);
	}
	value = find_key_and_return_value(key_buf);
	if (value == NULL)
	{
		free(key_buf);
		return (0);
	}
	while (*value)
	{
		error_check = make_string_and_link_node(NORMAL, *value);
		if (error_check < 0)
			break ;
		++value;
	}
	free(key_buf);
	return (error_check);
}
