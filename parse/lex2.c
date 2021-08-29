#include "../includes/minishell.h"

void	append_char_sub(char *tmp, char **buf, char ch, int size)
{
	ft_strlcpy(tmp, *buf, size + 1);
	tmp[size] = ch;
	tmp[size + 1] = '\0';
	free(*buf);
	*buf = tmp;
}

int	at_single_quote(char **line)
{
	int	error_check;

	error_check = make_string_and_link_node(NORMAL, '\0');
	if (error_check < 0)
		return (error_check);
	while (++(*line))
	{
		if (**line == '\'')
			return (0);
		else if (**line == '\0')
		{
			print_error(SYNTAX_ERROR, "lex");
			return (SYNTAX_ERROR);
		}
		error_check = make_string_and_link_node(NORMAL, **line);
		if (error_check < 0)
			return (error_check);
	}
	return (0);
}

int	at_double_quote(char **line)
{
	int		error_check;

	error_check = make_string_and_link_node(NORMAL, '\0');
	if (error_check < 0)
		return (error_check);
	while (++(*line))
	{
		if (**line == '\"')
			return (0);
		else if (**line == '$')
			error_check = expand_dollar_sign(line);
		else if (**line == '\0' || **line == '\\' || **line == ';')
		{
			print_error(SYNTAX_ERROR, "lex");
			error_check = SYNTAX_ERROR;
		}
		else
			error_check = make_string_and_link_node(NORMAL, **line);
		if (error_check < 0)
			break ;
	}
	return (error_check);
}

int	at_redirection_char(char **line)
{
	int	error_check;

	error_check = make_string_and_link_node(LEX_FINAL_WO_CHAR, 0);
	if (error_check < 0)
		return (error_check);
	if (**line == '>' || **line == '<')
	{
		if (**line == *(*line + 1))
			error_check = make_string_and_link_node(NORMAL, *((*line)++));
		if (error_check < 0)
			return (error_check);
	}
	error_check = make_string_and_link_node(NORMAL, **line);
	if (error_check < 0)
		return (error_check);
	error_check = make_string_and_link_node(NORMAL, (char)(-1));
	if (error_check < 0)
		return (error_check);
	error_check = make_string_and_link_node(LEX_FINAL_WO_CHAR, 0);
	if (error_check < 0)
		return (error_check);
	return (0);
}

int	at_white_spaces(char **line)
{
	int	error_check;

	error_check = make_string_and_link_node(LEX_FINAL_WO_CHAR, 0);
	if (error_check < 0)
		return (error_check);
	while (ft_isspace(*(++*line)))
		;
	(*line)--;
	return (0);
}
