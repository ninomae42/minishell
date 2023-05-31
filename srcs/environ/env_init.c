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

void	env_free_all_node(t_env_node *head)
{
	t_env_node	*next;

	while (head != NULL)
	{
		next = head->next;
		free(head->name);
		free(head->value);
		free(head->str);
		free(head);
		head = next;
	}
}

void	env_dealloc(t_env *env)
{
	env_free_all_node(env->head);
	free(env);
}
