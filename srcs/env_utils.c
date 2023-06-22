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
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
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

void	env_print(t_env *env)
{
	t_env_node	*node;

	if (env == NULL)
		return ;
	node = env->head;
	while (node != NULL)
	{
		printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
}
