#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	echo(char **argv)
{
	size_t	i;
	bool	need_space;
	bool	need_newline;

	i = 1;
	need_newline = true;
	if (argv[1] != NULL && strncmp(argv[1], "-n", 2) == 0)
	{
		i++;
		need_newline = false;
	}
	need_space = false;
	while (argv[i])
	{
		if (need_space)
			write(STDOUT_FILENO, " ", 1);
		need_space = true;
		write(STDOUT_FILENO, argv[i], strlen(argv[i]));
		i++;
	}
	if (need_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 1)
		return (EXIT_FAILURE);
	return (echo(argv));
}
