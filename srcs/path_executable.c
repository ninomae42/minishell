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

bool	path_is_valid_full_path(char *path)
{
	if (!path_is_exist(path))
	{
		err_perror_with_path(ENOENT, path);
		return (false);
	}
	if (path_is_directory(path))
	{
		err_is_directory(path);
		return (false);
	}
	return (true);
}

bool	path_is_valid_current_path(char *path, char *filename)
{
	if (!path_is_exist(path))
	{
		err_perror_with_path(ENOENT, filename);
		return (false);
	}
	if (path_is_directory(path))
	{
		err_is_directory(filename);
		return (false);
	}
	return (true);
}

char	*path_get_executable(char *filename)
{
	char	*env_path;
	char	*res_path;

	if (filename == NULL)
		return (NULL);
	if (path_is_contain_slash(filename))
	{
		if (!path_is_valid_full_path(filename))
			return (NULL);
		return (ft_strdup(filename));
	}
	env_path = getenv("PATH");
	if (env_path == NULL)
		env_path = ".";
	// if (path == NULL || path[0] == '\0')
	// 	path = _PATH_DEFPATH;
	res_path = get_executable_internal(env_path, filename);
	if (!path_is_valid_current_path(res_path, filename))
	{
		free(res_path);
		return (NULL);
	}
	return (res_path);
}
