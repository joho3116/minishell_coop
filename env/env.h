typedef struct s_env_node
{
	char	*key;
	char	*value;
}				t_env_node;

int	init_minishell_envp(char *envp[]);

void	malloc_and_strcpy_key_value(char *env, char **key, char **value);

t_env_node	*make_env_node(char **key, char **value);

int	ft_key_len(char *str);


////////////////////////////////////////
// 아래는 환경변수 관련하여 사용 가능한 api

// key의 value를 new_value로 교체
// new_value는 동적할당된 것이어야 함
// key를 찾지 못할 경우 음수값 리턴
// new_value == NULL이면 unset해버리기?
// 호출 후 new_value에는 노드에 넣은 스트링 주소가 있으므로 건들지 않게 주의
int	set_new_value_to_existing_key(char *key, char *new_value);

// key 찾아서 해당 노드 전부 free
// 못 찾으면 그냥 무시
void	find_key_and_unset(char *key);

// "key=value"형태의 스트링 받아서
// 환경변수 리스트에 addback해준다.
// 동적할당 실패시 음수 리턴
int	set_new_key(char *key_and_value);

char	**get_env_list(void);

int		count_env_num(void);

char	*unite_key_value(t_list *idx);

void	free_envp_list(char **envp);

char	*find_key_and_return_value(char *key);
