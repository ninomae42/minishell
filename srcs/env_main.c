#include "env.h"

char	*make_pair_str(char *name, char *value);

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
	node->pair_str = make_pair_str(name, value);
	node->next = NULL;
	return (node);
}

void	destroy_env(t_env *env)
{
	destroy_env_nodes(env->head);
	free(env);
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

char	*make_pair_str(char *name, char *value)
{
	size_t	alloc_size;
	char	*str;

	alloc_size = ft_strlen(name) + ft_strlen(value) + 2;
	str = (char *)malloc(sizeof(char) * alloc_size);
	if (str == NULL)
		ft_fatal("malloc");
	ft_strlcpy(str, name, alloc_size);
	ft_strlcat(str, "=", alloc_size);
	ft_strlcat(str, value, alloc_size);
	return (str);
}
