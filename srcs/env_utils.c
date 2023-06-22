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
