#include "environ.h"

char	*env_entry_new_str(const char *name, const char *value)
{
	size_t	alloc_size;
	char	*res;

	alloc_size = ft_strlen(name) + 1 + ft_strlen(value) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, name, alloc_size);
	ft_strlcat(res, "=", alloc_size);
	ft_strlcat(res, value, alloc_size);
	return (res);
}

void	env_entry_print(t_env *env)
{
	t_env_node	*current;

	current = env->head;
	while (current != NULL)
	{
		printf("%s\n", current->str);
		current = current->next;
	}
}

size_t	env_entry_size(t_env *env)
{
	return (env->size);
}

char	**env_entry_alloc_environ(t_env *env)
{
	char	**res;
	size_t	i;
	t_env_node	*current;

	res = (char **)malloc(sizeof(char *) * (env->size + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	current = env->head;
	while (current != NULL)
	{
		res[i] = current->str;
		i++;
		current = current->next;
	}
	res[i] = NULL;
	return (res);
}
