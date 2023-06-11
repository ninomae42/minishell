#include "ft_path.h"

static char	*concat_path(char *dir, char *filename)
{
	size_t	path_len;
	char	*path;

	path_len = ft_strlen(dir) + ft_strlen(filename) + 2;
	path = (char *)malloc(sizeof(char) * path_len);
	if (path == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(path, dir, path_len);
	ft_strlcat(path, "/", path_len);
	ft_strlcat(path, filename, path_len);
	return (path);
}

static char	*search_binary_internal(char **dirs, char *filename)
{
	char	*path;

	while (*dirs != NULL)
	{
		if (*dirs[0] == '\0')
		{
			path = concat_path(".", filename);
			if (access(path, F_OK) == 0)
				return (path);
		}
		else
		{
			path = concat_path(*dirs, filename);
			if (access(path, F_OK) == 0)
				return (path);
		}
		free(path);
		dirs++;
	}
	return (NULL);
}

char	*path_search_binary_path(char *search_dir, char *filename)
{
	char	**dirs;
	char	*res_path;

	dirs = path_dir_split(search_dir);
	if (dirs == NULL)
		return (NULL);
	res_path = search_binary_internal(dirs, filename);
	dir_free(dirs);
	return (res_path);
}
