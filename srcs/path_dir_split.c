#include "ft_path.h"

char	**path_split_dirs(char *env_path)
{
	char	**dirs;

	errno = 0;
	dirs = ft_split(env_path, ':');
	if (dirs == NULL)
	{
		if (errno == 0)
			errno = EINVAL;
		perror("ft_split");
		exit(EXIT_FAILURE);
	}
	return (dirs);
}

void	dir_free(char **dir)
{
	size_t	i;

	i = 0;
	while (dir[i])
	{
		free(dir[i]);
		i++;
	}
	free(dir[i]);
}

void	dir_print(char **dir)
{
	size_t	i;

	i = 0;
	while (dir[i])
	{
		printf("%s\n", dir[i]);
		i++;
	}
	printf("\n");
}
