#include "../includes/minishell.h"

// 렉서가 구분한 토큰을 바탕으로 각 커맨드마다 몇 개의 토큰을 위해
// malloc해야하는지 카운트해서 parsecnt변수에 넣어준다.
// parsecnt.num_of_cmds에는 커맨드 갯수를,
// parsecnt.num_of_tokens_in_one_command
int	count_parse(t_count_info_in_parse *parsecnt, t_list *idx)
{
	int		token_check;
	int		*inttmp;
	void	*nodtmp;
	int		token_cnt; // 커맨드별 토큰 갯수

	token_cnt = 0; // 초기화
	while (idx != NULL)
	{
		token_check = ft_which_redirection_token((char *)idx->data); // 어떤 토큰인지 리턴값으로 받는다.
		if (token_check == PIPE)
		{	// 파이프이면 새 커맨드로 넘어가는 신호로 인식,
			// 커맨드 갯수 카운트 늘리고,
			// lst_add_num_of_args통해 토큰 갯수를 parsecnt.num_of_tokens_in_one_command에 달아준다.
			parsecnt->num_of_cmds++;
			if (lst_add_num_of_tokens(parsecnt, token_cnt) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			token_cnt = 0;
		}
		else // >, <, >>, <<리디렉션 또는 일반 토큰인 경우 여기로
			token_cnt++;
		idx = idx->next;
	}
	// 마지막 커맨드는 while문 안에서 못 넣어줬기 때문에 넣어주기 위한 장치
	parsecnt->num_of_cmds++;
	if (lst_add_num_of_tokens(parsecnt, token_cnt) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (0); // 정상종료
}

// 토큰 스트링 받아서 어떤 종류인지 정수값으로 리턴
int	ft_which_redirection_token(char *str)
{
	if (str[0] == '\0' || str[1] == '\0') // 세그폴트 방지용
		return (NOT_REDIR);
	if (str[0] == '>' && str[1] == -1)
		return (OUT_REDIR);
	else if (str[0] == '<' && str[1] == -1)
		return (IN_REDIR);
	else if (str[0] == '|' && str[1] == -1)
		return (PIPE);
	if (str[2] == '\0')
		return (NOT_REDIR); // 세그폴트 방지용
	else if (str[0] == '>' && str[1] == '>' && str[2] == -1)
		return (OUT_REDIR_APP);
	else if (str[0] == '<' && str[1] == '<' && str[2] == -1)
		return (IN_REDIR_LIM);
	else
		return (NOT_REDIR);
}

// 노드 동적할당한 후 (int *)동적할당해서 args_cnt값으로 설정 후 노드에 달아준다.
// 그 다음 parsecnt.num_of_tokens_in_one_cmd에 노드를 추가해준다.
int	lst_add_num_of_tokens(t_count_info_in_parse *parsecnt, int args_cnt)
{
	int		*inttmp;
	t_list	*nodtmp;

	inttmp = malloc_int_and_set_num(args_cnt); // 동적할당 리턴
	if (inttmp == NULL)
	{
		ft_perror("parse");
		return (MALLOC_ERROR);
	}
	nodtmp = ft_lstnew(inttmp); // 동적할당 리턴
	if (nodtmp == NULL)
	{
		ft_perror("parse");
		free(inttmp);
		return (MALLOC_ERROR);
	}
	ft_lstadd_back(&(parsecnt->num_of_tokens_in_one_cmd), nodtmp);
	return (0);
}

int	*malloc_int_and_set_num(int num)
{
	int	*tmp;

	tmp = (int *)malloc(sizeof(int));
	if (tmp == NULL)
		return (NULL);
	*tmp = num;
	return (tmp);
}
