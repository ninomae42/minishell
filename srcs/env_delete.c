#include "env.h"

static int	delete_node_by_name(t_env *env, char *name);

int	env_unset(t_env *env, char *name)
{
	if (!env_is_name_valid(name) || env == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	return (delete_node_by_name(env, name));
}

static int	find_target_and_prev(t_env_node *head, char *name,
								t_env_node **target, t_env_node **prev)
{
	t_env_node	*internal_prev;

	internal_prev = head;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, name) == 0)
		{
			*target = head;
			*prev = internal_prev;
			return (0);
		}
		internal_prev = head;
		head = head->next;
	}
	return (-1);
}

static int	delete_node_by_name(t_env *env, char *name)
{
	t_env_node	*target;
	t_env_node	*prev;

	if (find_target_and_prev(env->head, name, &target, &prev) < 0)
		return (-1);
	if (target == env->head && target == env->tail)
	{
		env->head = NULL;
		env->tail = NULL;
	}
	else if (target == env->head)
		env->head = target->next;
	else if (target == env->tail)
		env->tail = prev;
	prev->next = target->next;
	if (target->pair_str != NULL)
		env->export_size--;
	destroy_env_node(target);
	env->size--;
	return (0);
}
