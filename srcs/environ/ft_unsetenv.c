#include "environ.h"

static t_env_node	*env_find_before_node(t_env *env, const char *name);
static int	delete_node_by_name(t_env *env, const char *name);

int	ft_unsetenv(t_env *env, const char *name)
{
	if (!is_env_name_valid(name))
	{
		errno = EINVAL;
		return (-1);
	}
	return (delete_node_by_name(env, name));
}

static t_env_node	*env_find_before_node(t_env *env, const char *name)
{
	t_env_node	*current;
	t_env_node	*prev;

	if (env == NULL || env->head == NULL)
		return (NULL);
	current = env->head;
	prev = env->head;
	while (current != NULL)
	{
		if (strcmp(current->name, name) == 0)
			return (prev);
		prev = current;
		current = current->next;
	}
	return (NULL);
}

static int	delete_node_by_name(t_env *env, const char *name)
{
	t_env_node	*prev;
	t_env_node	*target;
	t_env_node	*next;

	prev = env_find_before_node(env, name);
	if (prev == NULL)
		return (-1);
	target = prev->next;
	if (target == NULL)
		return (-1);
	next = target->next;
	prev->next = next;
	free(target->name);
	free(target->value);
	free(target->str);
	free(target);
	env->size--;
	return (0);
}
