#include "environ.h"

char	*ft_getenv(t_env *env, const char *name)
{
	t_env_node	*current;

	if (!is_env_name_valid(name))
	{
		errno = EINVAL;
		return (NULL);
	}
	current = env->head;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
