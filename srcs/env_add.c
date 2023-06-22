#include "env.h"

static void	env_add_new_env_node(t_env *env, char *name, char *value);
static void	env_replace_value(t_env_node *target, char *value);

int	env_set(t_env *env, char *name, char *value, int overwrite)
{
	t_env_node	*target;

	errno = 0;
	target = env_find_node(env, name);
	if (errno == EINVAL)
		return (-1);
	else if (overwrite == 0)
		return (0);
	if (target != NULL)
		env_replace_value(target, value);
	else
		env_add_new_env_node(env, name, value);
	return (0);
}

static void	env_add_new_env_node(t_env *env, char *name, char *value)
{
	t_env_node	*node;
	t_env_node	tmp;

	tmp.name = ft_strdup(name);
	if (value != NULL)
		tmp.value = ft_strdup(value);
	else
		tmp.value = ft_strdup("");
	if (tmp.name == NULL || tmp.value == NULL)
		ft_fatal("malloc");
	tmp.pair_str = make_pair_str(name, value);
	node = new_env_node(tmp.name, tmp.value, tmp.pair_str);
	if (env->head == NULL)
		env->head = node;
	else
		env->tail->next = node;
	env->tail = node;
	env->size++;
}

static void	env_replace_value(t_env_node *target, char *value)
{
	char	*dup_value;
	char	*pair_str;

	if (value != NULL)
		dup_value = ft_strdup(value);
	else
		dup_value = ft_strdup("");
	if (dup_value == NULL)
		ft_fatal("malloc");
	pair_str = make_pair_str(target->name, value);
	free(target->value);
	free(target->pair_str);
	target->value = dup_value;
	target->pair_str = pair_str;
}