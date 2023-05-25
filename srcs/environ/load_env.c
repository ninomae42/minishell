#include "tokenizer.h"
#include "environ.h"

static t_env_node	*parse_set_env_var_entry(t_env_node *current, char *entry)
{
	t_env_node	*node;
	char		*name;
	char		*value;
	char		*delm;

	delm = strchr(entry, '=');
	if (delm == NULL)
		return (NULL);
	name = strndup(entry, delm - entry);
	if (name == NULL)
		return (NULL);
	value = strdup(delm + 1);
	if (value == NULL)
	{
		free(name);
		return (NULL);
	}
	node = env_new_node(current, name, value);
	return (node);
}

int	load_env(t_env *env, char **environ)
{
	t_env_node	head;
	t_env_node	*current;

	if (environ == NULL)
		return (-1);
	head.next = NULL;
	current = &head;
	while (*environ != NULL)
	{
		current = parse_set_env_var_entry(current, *environ);
		if (current == NULL)
		{
			env_free_all_node(head.next);
			return (-1);
		}
		environ++;
	}
	env->head = head.next;
	env->tail = current;
	return (0);
}
