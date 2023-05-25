#include "environ.h"
#include "utils.h"

t_env	*env_new(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		perror_exit("malloc");
	env->head = NULL;
	env->tail = NULL;
	return (env);
}

t_env_node	*env_new_node(t_env_node *current, char *name, char *value)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		perror_exit("malloc");
	node->name = name;
	node->value = value;
	node->next = NULL;
	current->next = node;
	return (node);
}

void	env_free_all_node(t_env_node *head)
{
	t_env_node	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = next;
	}
}

void	env_dealloc(t_env *env)
{
	env_free_all_node(env->head);
	free(env);
}
