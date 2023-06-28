#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(int argc, char **argv)
{
	if (argc != 2)
		return 1;

	char	*path = argv[1];
	char	*parent;
	char	*last_slash;

	last_slash = strrchr(path, '/');
	if (last_slash == NULL || (last_slash == path))
		parent = strdup("/");
	else
		parent = strndup(path, last_slash - path);
	printf("[%s]\n", parent);
	free(parent);
}
