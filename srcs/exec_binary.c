#include "exec.h"

void	validate_path(char *path)
{
	if (!path_is_exist(path))
	{
		err_perror_with_path(errno, path);
		exit(127);
	}
	if (path_is_directory(path))
	{
		err_is_directory(path);
		exit(127);
	}
}

void	validate_path_current(char *path, char *filename)
{
	if (!path_has_exec_right(path))
	{
		err_perror_with_path(errno, filename);
		exit(127);
	}
	if (path_is_directory(path))
	{
		err_is_directory(filename);
		exit(127);
	}
}

char	*search_binary_internal(char **dirs, char *filename)
{
	char	*path;

	while (*dirs)
	{
		if (*dirs[0] == '\0')
			path = concat_path(".", filename);
		else
			path = concat_path(*dirs, filename);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	return (NULL);
}

char	*build_binary_path(char *search_dir, char *filename)
{
	char	**dirs;
	char	*res_path;

	dirs = path_dir_split(search_dir);
	if (dirs == NULL)
		err_fatal(errno);
	res_path = search_binary_internal(dirs, filename);
	dir_free(dirs);
	return (res_path);
}

void	exec(t_cmd_node *command)
{
	char	*command_name;
	char	*env_path;

	if (command == NULL || command->argv == NULL)
		exit(EXIT_FAILURE);
	if (command->argv[0] == NULL || command->argv[0][0] == '\0')
		exit(EXIT_SUCCESS);
	command_name = command->argv[0];
	if (*command_name == '/' || path_is_contain_slash(command_name))
	{
		validate_path(command_name);
		command->binary_path = command_name;
	}
	else
	{
		env_path = env_get_value(g_env, "PATH");
		if (env_path != NULL)
		{
			command->binary_path = build_binary_path(env_path, command_name);
			if (command->binary_path == NULL || path_is_directory(command->binary_path))
			{
				err_command_not_found(command_name);
				exit(127);
			}
		}
		else
		{
			// build binary path from current dir
			command->binary_path = build_binary_path(".", command_name);
			if (command->binary_path == NULL)
				err_command_not_found(command_name);
			validate_path_current(command->binary_path, command_name);
		}
	}
	if (execve(command->binary_path, command->argv, command->environ) < 0)
		err_fatal(errno);
}
