#include "env.h"

t_env_node	*env_find_node(t_env *env, char *name)
{
	t_env_node	*current;

	if (!env_is_name_valid(name) || env == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	current = env->head;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	env_is_name_valid(char *name)
{
	if (name == NULL || *name == '\0')
		return (false);
	if (ft_strchr(name, '=') != NULL)
		return (false);
	return (true);
}

char	*make_pair_str(char *name, char *value)
{
	size_t	alloc_size;
	char	*str;

	alloc_size = ft_strlen(name) + ft_strlen(value) + 2;
	str = (char *)malloc(sizeof(char) * alloc_size);
	if (str == NULL)
		ft_fatal("malloc");
	ft_strlcpy(str, name, alloc_size);
	ft_strlcat(str, "=", alloc_size);
	ft_strlcat(str, value, alloc_size);
	return (str);
}

char	**env_list_to_environ(t_env *env)
{
	char		**strs;
	t_env_node	*node;
	size_t		i;

	strs = (char **)malloc(sizeof(char *) * (env->size + 1));
	if (strs == NULL)
		ft_fatal("malloc");
	i = 0;
	node = env->head;
	while (node != NULL)
	{
		strs[i++] = node->pair_str;
		node = node->next;
	}
	strs[i] = NULL;
	return (strs);
}
