#include "env.h"
#include "minishell.h"

static int	parse_environ_str(t_env *env, char *str);

int	env_load_environ(t_env *env, char **environ)
{
	if (environ == NULL)
		return (-1);
	while (*environ != NULL)
	{
		parse_environ_str(env, *environ);
		environ++;
	}
	return (0);
}

static int	parse_environ_str(t_env *env, char *str)
{
	char	*delimiter;
	char	*name;
	char	*value;
	int		res;

	delimiter = ft_strchr(str, '=');
	if (delimiter == NULL)
		return (-1);
	name = ft_strndup(str, delimiter - str);
	value = ft_strdup(delimiter + 1);
	if (name == NULL || value == NULL)
		err_fatal(errno);
	res = env_set(env, name, value, 1);
	if (res < 0)
		err_env_name_not_valid(name);
	free(name);
	free(value);
	return (res);
}
