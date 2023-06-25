#include "builtin.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alphanum_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_identifier(char *name)
{
	if (name == NULL)
		return (false);
	if (!is_alpha_under(*name))
		return (false);
	name++;
	while (*name)
	{
		if (!is_alphanum_under(*name))
			return (false);
		name++;
	}
	return (true);
}

int		builtin_unset(char **argv)
{
	size_t	i;
	int		res;

	i = 1;
	res = EXIT_SUCCESS;
	while (argv[i])
	{
		if (is_identifier(argv[i]))
			env_unset(g_env, argv[i]);
		else
		{
			err_identifier("unset", argv[i]);
			res = EXIT_FAILURE;
		}
		i++;
	}
	return (res);
}
