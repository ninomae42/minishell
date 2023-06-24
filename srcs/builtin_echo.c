#include "builtin.h"

int	builtin_echo(char **argv)
{
	size_t	i;
	bool	need_space;
	bool	need_newline;

	i = 1;
	need_newline = true;
	if (argv[1] != NULL && ft_strncmp(argv[1], "-n", 2) == 0)
	{
		i++;
		need_newline = false;
	}
	need_space = false;
	while (argv[i])
	{
		if (need_space)
			ft_putchar_fd(' ', STDOUT_FILENO);
		need_space = true;
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
	}
	if (need_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
