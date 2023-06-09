#include "environ.h"

static int	parse_env_entry(t_env *env, char *entry);
static int	duplicate_entry_value(t_env_node *node_val, char *entry);

int	load_env(t_env *env, char **environ)
{
	if (environ == NULL)
		return (-1);
	while (*environ != NULL)
	{
		if (parse_env_entry(env, *environ) < 0)
		{
			env_free_env_nodes(env);
			return (-1);
		}
		environ++;
	}
	return (0);
}

static int	parse_env_entry(t_env *env, char *entry)
{
	t_env_node	node_val;

	if (duplicate_entry_value(&node_val, entry) < 0)
		return (-1);
	if (env_node_new(env, node_val.name, node_val.value, node_val.str) < 0)
	{
		free(node_val.name);
		free(node_val.value);
		free(node_val.str);
		return (-1);
	}
	return (0);
}

static int	duplicate_entry_value(t_env_node *node_val, char *entry)
{
	char	*delimiter;

	delimiter = strchr(entry, '=');
	if (delimiter == NULL)
		return (-1);
	node_val->name = strndup(entry, delimiter - entry);
	node_val->value = strdup(delimiter + 1);
	node_val->str = strdup(entry);
	if (node_val->name == NULL || node_val->value == NULL || node_val->str == NULL)
	{
		free(node_val->name);
		free(node_val->value);
		free(node_val->str);
		return (-1);
	}
	return (0);
}
