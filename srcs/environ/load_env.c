#include "tokenizer.h"
#include "environ.h"

static t_env_node	*parse_set_env_var_entry(t_env_node *current, char *entry)
{
	char		*name;
	char		*value;
	char		*delm;

	delm = strchr(entry, '=');
	if (delm == NULL)
		return (NULL);
	name = strndup(entry, delm - entry);
	value = strdup(delm + 1);
	entry = strdup(entry);
	if (name == NULL || value == NULL || entry == NULL)
	{
		free(name);
		free(value);
		free(entry);
		return (NULL);
	}
	return (env_new_node(current, name, value, entry));
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
