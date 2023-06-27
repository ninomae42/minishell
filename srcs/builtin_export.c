#include "builtin.h"
#include "expander.h"

void	print_env_node(t_env_node *node)
{
	char	*escaped_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->name, STDOUT_FILENO);
	if (node->value)
	{
		escaped_value = get_escaped_str(node->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	export_print(void)
{
	t_env_node	*node;
	t_env_node	*next;

	// TODO: sort environment node list
	node = g_env->head;
	while (node)
	{
		next = node->next;
		print_env_node(node);
		node = next;
	}
	return (EXIT_SUCCESS);
}

char	*get_identifier(char *export_input)
{
	char	*delim;
	char	*identifier;

	if (*export_input == '\0')
		return (NULL);
	delim = ft_strchr(export_input, '=');
	if (delim == NULL)
		identifier = ft_strdup(export_input);
	else
		identifier = ft_strndup(export_input, delim - export_input);
	if (identifier == NULL)
		err_fatal(errno);
	return (identifier);
}

bool	is_identifier_str(char *s)
{
	if (s == NULL)
		return (false);
	if (!is_alpha_under(*s))
		return (false);
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

void	add_exported_env_var(char *export_input)
{
	char	*delim;
	char	*name;
	char	*value;

	delim = ft_strchr(export_input, '=');
	if (delim != NULL)
	{
		name = ft_strndup(export_input, delim - export_input);
		if (name == NULL)
			err_fatal(errno);
		value = delim + 1;
	}
	else
	{
		name = ft_strdup(export_input);
		if (name == NULL)
			err_fatal(errno);
		value = NULL;
	}
	env_set(g_env, name, value, 1);
	free(name);
}

int	export_set_environs(char **argv)
{
	int		res;
	size_t	i;
	char	*identifier;

	res = EXIT_SUCCESS;
	i = 1;
	while (argv[i])
	{
		identifier = get_identifier(argv[i]);
		if (is_identifier_str(identifier))
			add_exported_env_var(argv[i]);
		else
		{
			err_identifier("export", argv[i]);
			res = EXIT_FAILURE;
		}
		free(identifier);
		i++;
	}
	return (res);
}

int		builtin_export(char **argv)
{
	if (argv[1])
	{
		return (export_set_environs(argv));
	}
	else
		return (export_print());
	return (EXIT_SUCCESS);
}
