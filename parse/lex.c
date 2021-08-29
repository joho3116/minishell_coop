#include "../includes/minishell.h"

int	tokenize(char *line)
{
	int		error_check;

	error_check = 0;
	while (*line)
	{
		if (*line == '\'')
			error_check = at_single_quote(&line);
		else if (*line == '\"')
			error_check = at_double_quote(&line);
		else if (*line == '\\' || *line == ';')
			error_check = SYNTAX_ERROR;
		else if (*line == '$')
			error_check = expand_dollar_sign(&line);
		else if (*line == '>' || *line == '<' || *line == '|')
			error_check = at_redirection_char(&line);
		else if (*line == ' ')
			error_check = at_white_spaces(&line);
		else
			error_check = make_string_and_link_node(NORMAL, *line);
		if (error_check < 0)
			break ;
		line++;
	}
	return (tokenize_return_check(error_check));
}

void	free_in_lex(void)
{
	make_string_and_link_node(LEX_FOR_FREE, 0);
	ft_lstclear(&(g_info.lex_head), &free);
}

int	tokenize_return_check(int status)
{
	if (status == 0)
		return (make_string_and_link_node(LEX_FINAL_WO_CHAR, 0));
	else
		return (make_string_and_link_node(LEX_FOR_FREE, 0));
}

int	make_string_and_link_node(int mode, char ch)
{
	static char	*buf = NULL;
	t_list		*tmp;

	if (mode == LEX_FOR_FREE)
	{
		safe_free((void **)&buf);
		return (0);
	}
	if ((mode != LEX_FINAL_WO_CHAR) && (append_char(&buf, ch) < 0))
		return (MALLOC_ERROR);
	if (mode == LEX_FINAL_W_CHAR || mode == LEX_FINAL_WO_CHAR)
	{
		if (buf == NULL)
			return (0);
		tmp = ft_lstnew((void *)buf);
		if (tmp == NULL)
		{
			ft_perror("lex");
			safe_free((void **)&buf);
			return (MALLOC_ERROR);
		}
		buf = NULL;
		ft_lstadd_back(&(g_info.lex_head), tmp);
	}
	return (0);
}

int	append_char(char **buf, char ch)
{
	int		size;
	char	*tmp;

	if (buf == NULL)
		return (-1);
	if (*buf == NULL)
	{
		*buf = malloc(sizeof(char));
		if (*buf == NULL)
		{
			ft_perror("lex");
			return (MALLOC_ERROR);
		}
		*(*buf) = '\0';
	}
	size = ft_strlen(*buf);
	tmp = malloc(sizeof(char) * (size + 2));
	if (tmp == NULL)
	{
		ft_perror("lex");
		safe_free((void **)buf);
		return (MALLOC_ERROR);
	}
	append_char_sub(tmp, buf, ch, size);
	return (0);
}
