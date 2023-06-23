#include "exec.h"
#include "ft_err.h"
#include "ft_path.h"

typedef int	t_file_type;
# define ABSOLUTE 1
# define RELATIVE 2
# define BINARY_FILE 3

t_file_type	get_file_type(char *filename)
{
	if (*filename == '/')
		return (ABSOLUTE);
	if (path_is_contain_slash(filename))
		return (RELATIVE);
	return (BINARY_FILE);
}

bool	is_valid_path(char *path)
{
	if (!path_is_exist(path))
	{
		err_perror_with_path(errno, path);
		return (false);
	}
	if (path_is_directory(path))
	{
		err_is_directory(path);
		return (false);
	}
	return (true);
}

bool	is_valid_path_current(char *path, char *filename)
{
	if (!path_has_exec_right(path))
	{
		err_perror_with_path(errno, filename);
		return (false);
	}
	if (path_is_directory(path))
	{
		err_is_directory(filename);
		return (false);
	}
	return (true);
}

char	*cmd_find_binary_path(char *filename, t_env *env)
{
	char	*env_path;
	char	*path;

	env_path = env_get_value(env, "PATH");
	path = NULL;
	if (env_path != NULL)
	{
		path = path_search_binary_path(env_path, filename);
		if (path == NULL || path_is_directory(path))
			err_command_not_found(filename);
	}
	else
	{
		path = path_search_binary_path(".", filename);
		if (path != NULL && !is_valid_path_current(path, filename))
		{
			free(path);
			path = NULL;
		}
	}
	return (path);
}

char	*cmd_get_binary_path(char *filename, t_env *env)
{
	t_file_type	f_type;
	char		*path;

	if (filename == NULL)
		return (NULL);
	f_type = get_file_type(filename);
	path = NULL;
	if (f_type == ABSOLUTE || f_type == RELATIVE)
	{
		if (is_valid_path(filename))
			path = ft_strdup(filename);
	}
	else
	{
		path = cmd_find_binary_path(filename, env);
	}
	return (path);
}
