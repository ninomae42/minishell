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
	return (dest);
}

// malloced.
char	*get_current_working_directory(void)
{
	char	*tmp;
	char	*res;

	res = env_get_value(g_env, "PWD");
	if (res == NULL)
	{
		tmp = getcwd(0, 0);
		if (tmp == NULL)
			err_fatal(errno);
		res = ft_strdup(tmp);
		free(tmp);
	}
	else
		res = ft_strdup(res);
	if (res == NULL)
		err_fatal(errno);
	return (res);
}

char	*cd_get_absolute_path(char *dest)
{
	char	*path;
	char	*cwd;

	if (*dest == '/')
		path = ft_strdup(dest);
	else
	{
		cwd = get_current_working_directory();
		path = concat_path(cwd, dest);
		free(cwd);
	}
	if (path == NULL)
		err_fatal(errno);
	return (path);
}

void	set_new_pwd(char *new_dir)
{
	free(g_env->old_pwd);
	g_env->old_pwd = ft_strdup(g_env->pwd);
	if (g_env->old_pwd == NULL)
		err_fatal(errno);
	free(g_env->pwd);
	g_env->pwd = ft_strdup(new_dir);
	if (g_env->pwd == NULL)
		err_fatal(errno);
	env_set(g_env, "PWD", g_env->pwd, 1);
	env_set(g_env, "OLDPWD", g_env->old_pwd, 1);
}

int	change_directory(char *dest)
{
	char	*path;

	path = cd_get_absolute_path(dest);
	if (chdir(path) == 0)
	{
		set_new_pwd(path);
		free(path);
		return (0);
	}
	if (chdir(dest) == 0)
	{
		set_new_pwd(getcwd(0, 0));
		free(path);
		return (0);
	}
	return (-1);
}

int	builtin_cd(char **argv)
{
	char	*dest;
	int		res;

	dest = set_cd_destination(argv);
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
