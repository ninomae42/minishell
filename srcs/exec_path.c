#include "exec.h"
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

char	*cmd_find_binary_path(char *filename)
{
	char	*env_path;
	char	*path;

	env_path = getenv("PATH");
	path = NULL;
	if (env_path != NULL)
		path = path_search_binary_path(env_path, filename);
	else
		// do search for current dir
		;
	return (path);
}

char	*cmd_get_binary_path(char *filename)
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
		path = cmd_find_binary_path(filename);
		if (path == NULL)
			err_command_not_found(filename);
	}
	return (path);
}
