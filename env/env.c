#include "../includes/minishell.h"

#include <stdio.h>
int	init_minishell_envp(char *envp[])
{
	int			i;
	char		*key_tmp;
	char		*value_tmp;
	t_env_node	*data;
	t_list		*node;

	i = -1;
	key_tmp = NULL;
	value_tmp = NULL;
	while (envp[++i] != NULL)
	{
		if (set_new_key(envp[i]) < 0)
			return (-1);
	}
	return (0); // 정상 종료
}

// key_tmp와 value_tmp에 key랑 value 동적 할당해서 돌려준다.
// 실패하면 둘 다 NULL로 돌려준다.
// 실패시 따로 free해줄 것 없게 종료
void	malloc_and_strcpy_key_value(char *env, char **key, char **value)
{
	int		key_len;

	key_len = ft_key_len(env);
	*key = ft_strndup(env, key_len);
	if (*key == NULL)
	{
		*value = NULL;
		return ;
	}
	*value = ft_strdup(env + key_len + 1);
	if (*value == NULL)
	{
		free(*key), *key = NULL;
		return ;
	}
	return ;
}

// key랑 value스트링 받아서 t_env_node동적할당한 다음 넣어주고 return
// 실패시 key랑 value free하고 NULL 반환
// 실패하든 성공하든 key랑 value에는 NULL 달아서 종료
t_env_node	*make_env_node(char **key, char **value)
{
	t_env_node	*ret;

	ret = (t_env_node *)malloc(sizeof(t_env_node));
	if (ret == NULL)
	{
		free(*key), free(*value), *key = NULL;
		*value = NULL;
		return (NULL);
	}
	ret->key = *key;
	ret->value = *value;
	*key = NULL;
	*value = NULL;
	return (ret);
}

// 환경변수 스트링 받아서 '=' 전까지의 길이 반환
int	ft_key_len(char *str)
{
	int	i;

	if (str == NULL)
		return (-1);
	i = -1;
	while (str[++i] != '=' && str[i] != '\0')
		;
	if (str[i] == '\0')
		return (-1);
	return (i);
}

////////////////////

// key의 value를 new_value로 교체
// new_value는 동적할당된 것이어야 함
// key를 찾지 못할 경우 음수값 리턴
// new_value == NULL이면 unset해버리기?
// 호출 후 new_value에는 노드에 넣은 스트링 주소가 있으므로 건들지 않게 주의
int	set_new_value_to_existing_key(char *key, char *new_value)
{
	t_list	*idx;

	idx = g_info.env;
	while (idx)
	{
		if (ft_strcmp(key, ((t_env_node*)(idx->data))->key) == 0)
			break ;
		idx = idx->next;
	}
	if (idx == NULL)
		return (-1);
	free(((t_env_node*)(idx->data))->value);
	((t_env_node*)(idx->data))->value = new_value;
	return (0);
}

// key 찾아서 해당 노드 전부 free
// 못 찾으면 그냥 무시
void	find_key_and_unset(char *key)
{
	t_list *idx;
	t_list	*before_idx;

	before_idx = NULL;
	idx = g_info.env;
	while (idx)
	{
		if (ft_strcmp(key, ((t_env_node*)(idx->data))->key) == 0)
			break ;
		before_idx = idx;
		idx = idx->next;
	}
	if (idx == NULL)
		return ;
	if (before_idx == NULL) // 첫 노드에서 key찾은 경우
		g_info.env = idx->next;
	else
		before_idx->next = idx->next;
	free(((t_env_node*)(idx->data))->key);
	free(((t_env_node*)(idx->data))->value);
	free(idx->data);
	free(idx);
}


// "key=value"형태의 스트링 받아서
// 환경변수 리스트에 addback해준다.
// 동적할당 실패시 음수 리턴
int	set_new_key(char *key_and_value)
{
	char		*key_tmp;
	char		*value_tmp;
	t_env_node	*data;
	t_list		*node;

	malloc_and_strcpy_key_value(key_and_value, &key_tmp, &value_tmp);
	if (key_tmp == NULL || value_tmp == NULL) // 사실 하나만 체크해도 되긴 함
	{
		print_error(MALLOC_ERROR, "set new key");
		return (-1);
	}
	data = make_env_node(&key_tmp, &value_tmp);
	if (data == NULL)
	{
		print_error(MALLOC_ERROR, "set new key");
		return (-1);
	}
	node = ft_lstnew((void *)data);
	if (node == NULL)
	{
		free(data->key);
		free(data->value);
		free(data);
		print_error(MALLOC_ERROR, "set new key");
		return (-1);
	}
	ft_lstadd_back(&(g_info.env), node);
}

// 호출하는 커맨드가 다양하므로 에러 문구를 해당 커맨드에서 출력하게 한다.
// 따라서 호출하는 함수에서 에러 출력하는 것 잊지 않기
char	**get_env_list(void)
{
	int		num_env;
	char	**ret;
	int		i;
	t_list	*idx;

	num_env = count_env_num();
	ret = (char **)malloc(sizeof(char *) * (num_env + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	idx = g_info.env;
	while (idx)
	{
		ret[i] = unite_key_value(i, idx);
		if (ret[i] == NULL)
		{
			free_envp_list(ret);
			return (NULL);
		}
		++i;
		idx = idx->next;
	}
	return (ret);
}

char	*unite_key_value(int i, t_list *idx)
{
	int		len;
	char	*ret;
	int		i_all;
	int		i_indiv;

	len = ft_strlen(((t_env_node *)(idx->data))->key)
		+ ft_strlen(((t_env_node *)(idx->data))->value) + 1;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i_all = 0;
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->key)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->key)[i_indiv++];
	ret[i_all++] = '=';
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->value)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->value)[i_indiv++];
	ret[i_all] = '\0';
	return (ret);
}

void	free_envp_list(char **envp)
{

}

// 각 주석 블럭마다 맨 앞에 테스트 설명 적어놓았습니다.
// 모두 valgrind로 메모리 누수 체크 완료

/* set_new_key 테스트(success)
t_info	g_info;

void	print_env(){
	t_list *idx;

	idx = g_info.env;
	while (idx){
		printf("key = %s, ", ((t_env_node*)(idx->data))->key);
		printf("value = %s\n", ((t_env_node*)(idx->data))->value);
		idx = idx->next;
	}
}

int main(){
	set_new_key("HELLO=WORLD");
	set_new_key("TEST=SUCCESS");
	print_env();
}
*/


/* init_minishell_envp()
** set_new_key()
** find_key_and_unset() 테스트 완료
t_info g_info;

void	print_env(){
	t_list *idx;

	idx = g_info.env;
	while (idx){
		printf("%s=", ((t_env_node*)(idx->data))->key);
		printf("\"%s\"\n", ((t_env_node*)(idx->data))->value);
		idx = idx->next;
	}
}

int main(int argc, char *argv[], char *envp[]){
	init_minishell_envp(envp);
	set_new_key("HELLO=WORLD");
	set_new_key("TEST=SUCCESS");
	print_env();
	printf("===================\n");
	find_key_and_unset("HELLO");
	print_env();
	printf("===================\n");
	find_key_and_unset("PATH");
	find_key_and_unset("HELLO");
	print_env();

}
*/


/*
** set_new_value_to_existing_key() 테스트 - 성공
t_info g_info;

void	print_env(){
	t_list *idx;

	idx = g_info.env;
	while (idx){
		printf("%s=", ((t_env_node*)(idx->data))->key);
		printf("\"%s\"\n", ((t_env_node*)(idx->data))->value);
		idx = idx->next;
	}
}

int main(int argc, char *argv[], char *envp[]){
	init_minishell_envp(envp);

	char *tmp = ft_strdup("teststring not a path");
	set_new_value_to_existing_key("PATH", tmp);

	print_env();

}
*/
