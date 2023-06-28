#include "builtin.h"
#include "expander.h"

bool	is_identifier_str(char *name)
{
	if (name == NULL)
		return (false);
	if (!is_alpha_under(*name))
		return (false);
	name++;
	while (*name)
	{
		if (!is_alpha_num_under(*name))
			return (false);
		name++;
	}
	return (true);
}

int	builtin_unset(char **argv)
{
	size_t	i;
	int		res;

	i = 1;
	res = EXIT_SUCCESS;
	while (argv[i])
	{
		if (is_identifier_str(argv[i]))
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
