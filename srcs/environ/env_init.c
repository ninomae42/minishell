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
	env->size = 0;
	return (env);
}

int	env_node_new(t_env *env, char *name, char *value, char *str)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		return (-1);
	node->name = name;
	node->value = value;
	node->str = str;
	node->next = NULL;
	if (env->head == NULL)
		env->head = node;
	else
		env->tail->next = node;
	env->tail = node;
	env->size++;
	return (0);
}

void	env_free_env_nodes(t_env *env)
{
	t_env_node	*current;
	t_env_node	*next;

	current = env->head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current->str);
		free(current);
		current = next;
	}
	env->size = 0;
	env->head = NULL;
	env->tail = NULL;
}


void	env_dealloc(t_env *env)
{
	env_free_env_nodes(env);
	free(env);
}
