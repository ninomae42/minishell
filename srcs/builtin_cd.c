/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:59:54 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 09:59:55 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_path.h"

char	*set_cd_destination(char **argv)
{
	char	*dest;

	if (argv[1] == NULL)
	{
		dest = env_get_value(g_env, "HOME");
		if (dest == NULL)
		{
			err_builtin_cd("HOME not set");
			return (NULL);
		}
		else
			dest = ft_strdup(dest);
	}
	else
		dest = ft_strdup(argv[1]);
	if (dest == NULL)
		err_perror(errno);
	return (dest);
}

char	*get_sys_cwd_path(char *caller);

void	setpwd(char *path);

char	*get_cannoned_path(char *cur_path);

int	set_new_pwd(void)
{
	char	*new_cwd;
	char	*dup;

	new_cwd = get_sys_cwd_path("cd");
	if (new_cwd == NULL)
		return (-1);
	dup = ft_strdup(new_cwd);
	if (dup == NULL)
		err_fatal(errno);
	setpwd(dup);
	free(new_cwd);
	free(dup);
	return (0);
}

char	*get_absolute_destination_path(char *dest)
{
	char	*cwd;
	char	*path;
	char	*cannoned_path;

	if (*dest == '/')
		path = ft_strdup(dest);
	else
	{
		cwd = getcwd(NULL, 0);
		if (cwd != NULL)
			path = concat_path(cwd, dest);
		else
			return (ft_strdup(dest));
		free(cwd);
	}
	if (path == NULL)
		err_fatal(errno);
	cannoned_path = get_cannoned_path(path);
	if (cannoned_path != NULL)
	{
		free(path);
		return (cannoned_path);
	}
	free(cannoned_path);
	return (path);
}

int	change_directory(char *dest)
{
	char	*absolute_dest;

	absolute_dest = get_absolute_destination_path(dest);
	if (chdir(absolute_dest) == 0)
	{
		free(absolute_dest);
		if (set_new_pwd() < 0)
			return (-1);
		return (0);
	}
	free(absolute_dest);
	return (-1);
}

int	builtin_cd(char **argv)
{
	char	*dest;
	int		res;

	dest = set_cd_destination(argv);
	if (dest == NULL)
		return (EXIT_FAILURE);
	if (change_directory(dest) == 0)
		res = EXIT_SUCCESS;
	else
	{
		err_builtin_cd_perror_with_path(errno, (char *)dest);
		res = EXIT_FAILURE;
	}
	free(dest);
	return (res);
}
