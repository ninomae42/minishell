#include "builtin.h"
#include "ft_err.h"
#include "minishell.h"

static bool	is_numeric_str(char *s)
{
	if (s == NULL || *s == '\0')
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

int		builtin_exit(char **argv)
{
	int	res;

	if (isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argv[1] == NULL)
		exit(g_env->status);
	if (is_numeric_str(argv[1]))
	{
		if (argv[2])
		{
			err_builtin_exit("too many arguments", NULL);
			return (EXIT_FAILURE);
		}
		errno = 0;
		res = ft_atoi(argv[1]);
		if (errno == 0)
			exit(res);
	}
	err_builtin_exit("numeric argument required", argv[1]);
	exit(255);
}
