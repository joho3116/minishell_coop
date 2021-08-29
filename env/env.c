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
