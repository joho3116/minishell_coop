// 토큰 단위로 커맨드 분해

// ex1)
// ls -al|cat<inputfile>outputfile
// => "ls" "-al" "|" "cat" "<" "inputfile" ">" "outputfile"

// ex2)
// ls "-al|cat<inputfile>outputfile"
// => "ls" "-al|cat<inputfile>outputfile"

// readline에서 받은 스트링을 토큰 단위로 분해해준다.
// 인자로 char **의 주소값(char ***)을 받아서 참조를 통해 분해한 스트링의 배열을 넘겨준다.

// 동적 할당 실패시 -1 반환, 정상 종료시 0 반환

//------------------------------------

// '$'의 확장도 이 단계에서 해줘야 할 것 같다.

// 함수 바깥에서 free등의 처리를 일관성 있게 하기 위해 아무 인자가 없는 빈 스트링이 들어온 경우에도 동적 할당을 하는 쪽으로 생각


#include "../includes/minishell.h"

// line이 nul문자를 만나서 정상적으로 while문을 탈출하면 tokenize_return_check에서 만들던 스트링 마무리 지어서 노드에 달아줘야 한다.
int		tokenize(char *line)
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


// 정상 status로 받는 경우 스트링 마무리 지어서 리스트에 달아줘야 한다.
int		tokenize_return_check(int status)
{
	if (status == 0)
		return (make_string_and_link_node(FINAL_WO_CHAR, 0));
	else
		return (make_string_and_link_node(FOR_FREE, 0));
}

///////////////////////////////////////

int		at_single_quote(char **line)
{
	make_string_and_link_node(NORMAL, '\0');
	while (++(*line))
	{
		if (**line == '\'')
			return (0);
		else if (**line == '\0')
			return (SYNTAX_ERROR);
		make_string_and_link_node(NORMAL, **line);
	}
	return (0);
}

int		at_double_quote(char **line)
{
	int		error_check;

	error_check = make_string_and_link_node(NORMAL, '\0');
	while (++(*line))
	{
		if (error_check < 0)
			break ;
		if (**line == '\"')
			return (0);
		else if (**line == '$')
		{
			expand_dollar_sign(line);
			// ++(*line);
			// if (**line == '?')
			// 	error_check = expand_exit_status_and_append_string();
			// else if (ft_isdigit(**line))
			// 	error_check = 0;
			// else if (ft_isalpha(**line))
			// 	error_check = find_env_var_and_mov_ptr(line);
			// else if (ft_isspace(**line))
			// 	error_check = make_string_and_link_node(NORMAL, '$');
		}
		else if (**line == '\0' || **line == '\\' || **line == ';')
			error_check = SYNTAX_ERROR;
		else
			error_check = make_string_and_link_node(NORMAL, **line);
	}
	return (error_check);
}

int		expand_dollar_sign(char **line)
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

int		at_redirection_char(char **line)
{
	int	error_check;

	error_check = make_string_and_link_node(FINAL_WO_CHAR, 0);
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
	error_check = make_string_and_link_node(FINAL_WO_CHAR, 0);
	if (error_check < 0)
		return (error_check);
	return (0);
}

int		at_white_spaces(char **line)
{
	int	error_check;

	error_check = make_string_and_link_node(FINAL_WO_CHAR, 0);
	if (error_check < 0)
		return (error_check);
	while (ft_isspace(*(++*line)))
		;
	(*line)--;
	return (0);
}
///////////////////////////////////////


int		expand_exit_status_and_append_string(void)
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
		return (MALLOC_ERROR);
	idx = -1;
	while (ascii_num[++idx] != 0)
	{
		error_check = make_string_and_link_node(NORMAL, ascii_num[idx]);
		if (error_check < 0)
		{
			safe_free((void **)&ascii_num);
			return (error_check);
		}
	}
	safe_free((void **)&ascii_num);
	return (0);
}

int		ft_is_in_expansion(char ch)
{
	return (!(ft_isspace(ch) || ch == '|' || ch == '>' || ch == '<' || ch == ';' || ch == '/'));
}

int		find_env_var_and_mov_ptr(char **line)
{
	char	*start;
	int		len;

	start = *line;
	while (!ft_is_in_expansion(*(++(*line))))
		;
	len = ((*line)--) - start;
	return (only_find_env_var(start, len));
}

int		only_find_env_var(char *start, int len)
{
	int	i;

	i = -1;
	while ((g_info.envp)[++i] != NULL)
	{
		if (ft_strncmp(start, (g_info.envp)[i], len) == 0 && (g_info.envp)[i][len] == '=')
		{
			while ((g_info.envp)[i][++len] != '\0')
			{
				if (make_string_and_link_node(NORMAL, (g_info.envp)[i][len]) < 0)
					return (MALLOC_ERROR);
			}
			return (0);
		}
	}
	return (0);
}






// INIT_STRING으로 호출될 때는 항상 그 직전에 string 마무리해서 node에 달아주고 buf는 NULL로 바꿔줬다고 전제..
// append_char에서 malloc 오류 발생시 안에서 free해주기(가급적 오류 발생한 단계에서 free해주기)
// '\0'문자를 ch에 넘겨주면 malloc 공간은 늘어나지만 스트링 내용은 그대로인 효과.
int		make_string_and_link_node(int mode, char ch)
{
	static char	*buf = NULL;
	t_list		*tmp;

	if (mode == FOR_FREE)
	{
		safe_free((void **)&buf);
		return (0);
	}
	// 일단 들어온 문자를 buf스트링에 달아준다
	if ((mode != FINAL_WO_CHAR) && (append_char(&buf, ch) < 0))
		return (MALLOC_ERROR);
	// 스트링 마무리 지어야 되면 노드 만들어서 달고 리스트에 추가. 그 후 buf에 NULL 할당
	if (mode == FINAL_W_CHAR || mode == FINAL_WO_CHAR)
	{
		if (buf == NULL)
			return (0);
		tmp = ft_lstnew((void *)buf);
		if (tmp == NULL)
		{
			safe_free((void **)&buf);
			return (MALLOC_ERROR);
		}
		buf = NULL;
		ft_lstadd_back(&(g_info.lex_head), tmp);
	}
	return (0);
}

int		append_char(char **buf, char ch)
{
	int		size;
	char	*tmp;

	if (buf == NULL)
		return (-1);
	if (*buf == NULL)
	{
		*buf = malloc(sizeof(char));
		if (*buf == NULL)
			return (MALLOC_ERROR);
		*(*buf) = '\0';
	}
	size = ft_strlen(*buf);
	tmp = malloc(sizeof(char) * (size + 2));
	if (tmp == NULL)
	{
		safe_free((void **)buf);
		return (MALLOC_ERROR);
	}
	ft_strlcpy(tmp, *buf, size + 1);
	tmp[size] = ch;
	tmp[size + 1] = '\0';
	free(*buf);
	*buf = tmp;
	return (0);
}

// syntax error일 때 lex 종료 직전 free할 것들 free해주는 함수
void	free_in_lex(void)
{
	make_string_and_link_node(FOR_FREE, 0);
	ft_lstclear(&(g_info.lex_head), &free);
}
