/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:39 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:40 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		exit(126);
	}
	if (!path_has_exec_right(path))
	{
		err_perror_with_path(errno, path);
		exit(126);
	}
}

void	validate_path_current(char *path, char *filename)
{
	if (path == NULL)
	{
		err_perror_with_path(ENOENT, filename);
		exit(127);
	}
	if (!path_is_exist(path))
	{
		err_perror_with_path(errno, path);
		exit(127);
	}
	if (!path_has_exec_right(path))
	{
		err_perror_with_path(errno, filename);
		exit(126);
	}
	if (path_is_directory(path))
	{
		err_is_directory(filename);
		exit(126);
	}
}

void	exec_from_environ_path(char *command_name, char **argv, char **envp)
{
	char	*env_path;
	char	*binary_path;

	env_path = env_get_value(g_env, "PATH");
	if (env_path != NULL && *env_path)
	{
		binary_path = build_binary_path(env_path, command_name);
		if (binary_path == NULL || path_is_directory(binary_path))
		{
			err_command_not_found(command_name);
			exit(127);
		}
	}
	else
	{
		binary_path = build_binary_path(".", command_name);
		validate_path_current(binary_path, command_name);
	}
	if (execve(binary_path, argv, envp) < 0)
		err_fatal(errno);
}

void	exec(char *command_name, char **argv, char **envp)
{
	if (command_name == NULL || argv == NULL)
		exit(EXIT_SUCCESS);
	if (*command_name == '/' || path_is_contain_slash(command_name))
	{
		validate_path(command_name);
		if (execve(command_name, argv, envp) < 0)
			err_fatal(errno);
	}
	else
		exec_from_environ_path(command_name, argv, envp);
}
