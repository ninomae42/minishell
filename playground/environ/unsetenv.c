#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void	printenv(char **environ)
{
	while (*environ != NULL)
	{
		if (strncmp("USER", *environ, 4) == 0)
		{
			printf("%s\n", *environ);
			break ;
		}
		environ++;
	}
}

int	main(void)
{
	printenv(environ);
	int	res = unsetenv("USER");
	printf("unsetenv_res: %d\n", res);
	printenv(environ);
}
