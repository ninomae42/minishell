#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern char **environ;


void	print_env(char **environ)
{
	while (*environ != NULL)
	{
		printf("%s\n", *environ);
		environ++;
	}
}

int	main(void)
{
	print_env(environ);
	exit(EXIT_SUCCESS);
}
