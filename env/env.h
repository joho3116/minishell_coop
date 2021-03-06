typedef struct s_env_node
{
	char	*key;
	char	*value;
}				t_env_node;

int	init_minishell_envp(char *envp[]);

void	malloc_and_strcpy_key_value(char *env, char **key, char **value);

t_env_node	*make_env_node(char **key, char **value);

char	*duplicate_only_value(char *key_value);

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


// 연결리스트 형태의 전역변수를 char **의 리스트로 동적할당해서 반환해준다.
// with_quotation버전은 export에서 key="value"형태로 출력하기에 이를 위한 함수
// 사용하고 free_env_list()로 해제해줘야 함
char	**get_env_list(void);
char	**get_env_list_with_quotation(void);

// 밸류 없는 노드도 카운트(get_env_list에 쓰임)
int		count_env_num_all(void);

// 밸류 없는 노드는 카운트 안 함(get_env_list_with_quotation에 쓰임)
int		count_env_num_exclude_null_value(void);

char	*unite_key_value(t_list *idx);
char	*unite_key_value_with_quotation(t_list *idx);

// get_env_list로 받은 이중 배열을 메모리 해제
void	free_envp_list(char **envp);

// 키 스트링을 주면 밸류 스트링을 반환(밸류 스트링은 전역변수에 있는 리스트의 원본이므로 수정하지 않게 주의)
char	*find_key_and_return_value(char *key);

// 키 스트링을 주면 해당 노드의 포인터를 반환, 못 찾으면 널 반환
t_list	*find_key_and_return_node(char *key);
char	*duplicate_only_value(char *key_value);
