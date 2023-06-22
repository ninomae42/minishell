#include "env.h"

char	*env_get_value(t_env *env, char *name)
{
	t_env_node	*node;

	node = env_find_node(env, name);
	if (node == NULL)
		return (NULL);
	return (node->value);
}

char	*env_get_pair_str(t_env *env, char *name)
{
	t_env_node	*node;

	node = env_find_node(env, name);
	if (node == NULL)
		return (NULL);
	return (node->pair_str);
}
