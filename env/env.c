#include "../includes/minishell.h"

#include <stdio.h>
int	init_minishell_envp(char *envp[])
{
	int			i;

	char		*key_tmp;
	char		*value_tmp;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (set_new_key(envp[i]) < 0)
			return (-1);
	}
	return (0);
}

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
	if (before_idx == NULL)
		g_info.env = idx->next;
	else
		before_idx->next = idx->next;
	free(((t_env_node*)(idx->data))->key);
	free(((t_env_node*)(idx->data))->value);
	free(idx->data);
	free(idx);
}

int	set_new_key(char *key_and_value)
{
	char		*key_tmp;
	char		*value_tmp;
	t_env_node	*data;
	t_list		*node;

	malloc_and_strcpy_key_value(key_and_value, &key_tmp, &value_tmp);
	if (key_tmp == NULL || value_tmp == NULL)
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
	return (0);
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
		ret[i] = unite_key_value(idx);
		if (ret[i] == NULL)
		{
			free_envp_list(ret);
			return (NULL);
		}
		++i;
		idx = idx->next;
	}
	ret[i] = NULL;
	return (ret);
}
char	**get_env_list_with_quotation(void)
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
		ret[i] = unite_key_value_with_quotation(idx);
		if (ret[i] == NULL)
		{
			free_envp_list(ret);
			return (NULL);
		}
		++i;
		idx = idx->next;
	}
	ret[i] = NULL;
	return (ret);
}

int		count_env_num()
{
	int		i;
	t_list	*idx;

	i = 0;
	idx = g_info.env;
	while (idx)
	{
		++i;
		idx = idx->next;
	}
	return (i);
}

char	*unite_key_value(t_list *idx)
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
char	*unite_key_value_with_quotation(t_list *idx)
{
	int		len;
	char	*ret;
	int		i_all;
	int		i_indiv;

	len = ft_strlen(((t_env_node *)(idx->data))->key)
		+ ft_strlen(((t_env_node *)(idx->data))->value) + 1 + 2;
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i_all = 0;
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->key)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->key)[i_indiv++];
	ret[i_all++] = '=';
	ret[i_all++] = '\"';
	i_indiv = 0;
	while ((((t_env_node *)(idx->data))->value)[i_indiv] != '\0')
		ret[i_all++] = (((t_env_node *)(idx->data))->value)[i_indiv++];
	ret[i_all++] = '\"';
	ret[i_all] = '\0';
	return (ret);
}

void	free_envp_list(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
	{
		free(envp[i]);
	}
	free(envp);
}

char	*find_key_and_return_value(char *key)
{
	t_list *idx;

	idx = g_info.env;
	while (idx)
	{
		if (ft_strcmp(key, ((t_env_node*)(idx->data))->key) == 0)
			break ;
		idx = idx->next;
	}
	if (idx == NULL)
		return (NULL);
	else
		return (((t_env_node*)(idx->data))->value);
}
