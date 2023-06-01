#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env_node	t_env_node;
struct s_env_node{
	char		*name;
	char		*value;
	char		*str;
	t_env_node	*next;
};

typedef struct s_env	t_env;
struct s_env{
	t_env_node	*head;
	t_env_node	*tail;
	size_t		size;
};

t_env	*env_new(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
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

int	duplicate_entry_value(t_env_node *node_val, char *entry)
{
	char		*delimiter;

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

int	env_node_parse_entry(t_env *env, char *entry)
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

int	load_env(t_env *env, char **environ)
{
	if (environ == NULL)
		return (-1);
	while (*environ != NULL)
	{
		if (env_node_parse_entry(env, *environ) < 0)
		{
			env_free_env_nodes(env);
			return (-1);
		}
		environ++;
	}
	return (0);
}

void	print_env(t_env *env)
{
	t_env_node	*head;

	head = env->head;
	while (head != NULL)
	{
		printf("n: %s, v: %s, e: %s\n", head->name, head->value, head->str);
		head = head->next;
	}
}

// extern char	**environ;
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_env	*env;

	env = env_new();
	if (env == NULL)
	{
		printf("env_new_failed\n");
		return (1);
	}
	printf("envp: %p\n", envp);
	printf("*envp: %p\n", *envp);
	// if (load_env(env, environ) < 0)
	if (load_env(env, envp) < 0)
	{
		printf("load_env_failed\n");
		return (1);
	}
	printf("num_of_env_entry: %zu\n", env->size);
	print_env(env);
	env_free_env_nodes(env);
	printf("num_of_env_entry: %zu\n", env->size);
	free(env);
	return (0);
}
