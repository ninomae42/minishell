#include "environ.h"

t_env_node	*env_find_node(t_env *env, const char *name)
{
	t_env_node	*current;

	if (!is_env_name_valid(name) || env == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	current = env->head;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	is_env_name_valid(const char *name)
{
	if (name == NULL || *name == '\0')
		return (false);
	if (strchr(name, '=') != NULL)
		return (false);
	return (true);
}

size_t	env_entry_len(t_env *env)
{
	t_env_node	*current;
	size_t		len;

	if (env == NULL)
		return (0);
	len = 0;
	current = env->head;
	while (current != NULL)
	{
		len++;
		current = current->next;
	}
	return (len);
}
