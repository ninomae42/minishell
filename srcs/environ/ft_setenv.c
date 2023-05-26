#include "environ.h"

static int	replace_target_value(t_env_node *target, const char *value);
static int	add_new_env_node(t_env *env, char *name, char *value);

int	ft_setenv(t_env *env, const char *name, const char *value, int overwrite)
{
	t_env_node	*target;

	errno = 0;
	target = env_find_node(env, name);
	if (errno == EINVAL)
		return (-1);
	else if (overwrite == 0)
		return (0);
	else if (target != NULL)
		return (replace_target_value(target, value));
	else
		return (add_new_env_node(env, (char *)name, (char *)value));
}

static int	replace_target_value(t_env_node *target, const char *value)
{
	char	*tmp;
	char	*entry;

	tmp = strdup(value);
	entry = env_entry_new_str(target->name, value);
	if (tmp == NULL || entry == NULL)
	{
		perror("malloc");
		free(tmp);
		free(entry);
		return (-1);
	}
	free(target->value);
	free(target->str);
	target->value = tmp;
	target->str = entry;
	return (0);
}

static int	add_new_env_node(t_env *env, char *name, char *value)
{
	t_env_node	*node;
	char		*entry;

	name = strdup(name);
	value = strdup(value);
	entry = env_entry_new_str(name, value);
	if (value == NULL)
	{
		free(name);
		free(value);
		free(entry);
		return (-1);
	}
	node = env_new_node(env->tail, name, value, entry);
	env->tail = node;
	env->size++;
	return (0);
}
