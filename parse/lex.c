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


#include "parse.h"

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
		else if (*line == '>' || *line == '<' || *line == '|')
			error_check = at_redirection_char(&line);
		else if (*line == ' ')
			error_check = at_white_spaces(&line);
		line++;
		if (error_check < 0)
			break ;
	}
	return (tokenize_return_check(error_check));
}


// 정상 status로 받는 경우 스트링 마무리 지어서 리스트에 달아줘야 한다.
int		tokenize_return_check(int status)
{
	if (status == 0)
		return (make_string_and_link_node(FINAL_CHAR, 0));
	else
		return (status);
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
		safe_free(&buf);
		return (0);
	}
	// 일단 들어온 문자를 buf스트링에 달아준다
	if (append_char(&buf, ch) < 0)
		return (MALLOC_ERROR);
	// 스트링 마무리 지어야 되면 노드 만들어서 달고 리스트에 추가. 그 후 buf에 NULL 할당
	if (mode == FINAL_CHAR)
	{
		if (buf == NULL)
			return (0);
		tmp = ft_lstnew((void *)buf);
		if (tmp == NULL)
		{
			safe_free(&buf);
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
		safe_free(buf);
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
