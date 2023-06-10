#include "ft_path.h"

char	*concat_path(char *dir, char *filename)
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

char	*get_executable_internal(char *env_path, char *filename)
{
	size_t	i;
	char	**dirs;
	char	*tmp_path;
	char	*exec_path;

	dirs = path_split_dirs(env_path);
	exec_path = NULL;
	i = 0;
	while (dirs[i] != NULL)
	{
		tmp_path = concat_path(dirs[i], filename);
		if (access(tmp_path, X_OK) == 0)
		{
			exec_path = tmp_path;
			break ;
		}
		free(tmp_path);
		i++;
	}
	dir_free(dirs);
	return (exec_path);
}

char	*path_search_binary_path(char *search_dir, char *filename)
{
	char	*res_path;

	res_path = get_executable_internal(search_dir, filename);
	return (res_path);
}
