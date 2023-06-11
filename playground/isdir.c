#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Returns whether path is a directory.
// If path is directory, then returns 1
// If path is not a directory, then returns 0
int	is_directory(char *path)
{
	struct stat	st;
	int			res;

	res = stat(path, &st);
	if (res != 0)
	{
		perror("stat");
		return (0);
	}
	return (S_ISDIR(st.st_mode));
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(EXIT_FAILURE);

	char	*path = argv[1];

	if (access(path, F_OK) < 0)
	{
		printf("minishell: %s: %s\n", path, strerror(errno));
		exit(EXIT_FAILURE);
	}
	if (is_directory(path))
		printf("minishell: %s: is a directory\n", path);
	else
		printf("%s is not a directory\n", path);
	exit(EXIT_SUCCESS);
}
