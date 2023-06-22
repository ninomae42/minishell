#include "env.h"

t_env	*new_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		ft_fatal("malloc");
	env->size = 0;
	env->head = NULL;
	env->tail = NULL;
	return (env);
}

t_env_node	*new_env_node(char *name, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		ft_fatal("malloc");
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	if (node->name == NULL || node->value == NULL)
		ft_fatal("malloc");
	node->pair_str = make_pair_str(name, value);
	node->next = NULL;
	return (node);
}

void	destroy_env(t_env *env)
{
	destroy_env_nodes(env->head);
	free(env);
}

void	destroy_env_node(t_env_node *node)
{
	free(node->name);
	free(node->value);
	free(node->pair_str);
	free(node);
}

void	destroy_env_nodes(t_env_node *head)
{
	t_env_node	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head->pair_str);
		free(head);
		head = next;
	}
}
