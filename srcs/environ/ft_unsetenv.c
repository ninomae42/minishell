#include "environ.h"

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

static int	env_find_target_node(t_env_node *head, const char *name,
						t_env_node **target, t_env_node **prev)
{
	t_env_node	*i_prev;

	if (head == NULL)
		return (-1);
	i_prev = head;
	while (head != NULL)
	{
		if (strcmp(head->name, name) == 0)
		{
			*prev = i_prev;
			*target = head;
			return (0);
		}
		i_prev = head;
		head = head->next;
	}
	*target = NULL;
	*prev = NULL;
	return (-1);
}

static int	delete_node_by_name(t_env *env, const char *name)
{
	t_env_node	*prev;
	t_env_node	*target;

	if (env == NULL)
		return (-1);
	if (env_find_target_node(env->head, name, &target, &prev) < 0)
		return (-1);
	if (prev == target)
		env->head = target->next;
	else
		prev->next = target->next;
	free(target->name);
	free(target->value);
	free(target->str);
	free(target);
	env->size--;
	return (0);
}
