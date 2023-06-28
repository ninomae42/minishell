#include "builtin.h"
#include "minishell.h"
#include "ft_path.h"

void	set_oldpwd(char *old_pwd)
{
	env_set(g_env, "OLDPWD", old_pwd, 1);
}

void	setpwd(char *path)
{
	char	*oldpwd;
	char	*dup;

	oldpwd = env_get_value(g_env, "PWD");
	if (oldpwd != NULL)
	{
		dup = ft_strdup(oldpwd);
		env_set(g_env, "OLDPWD", dup, 1);
		free(dup);
	}
	else
		env_set(g_env, "OLDPWD", oldpwd, 1);
	env_set(g_env, "PWD", path, 1);
}

char	*get_sys_cwd_path(char *caller)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd(caller, STDERR_FILENO);
		ft_putstr_fd(": error retriefving current directory: ", STDERR_FILENO);
		ft_putstr_fd("getcwd: ", STDERR_FILENO);
		ft_putstr_fd("cannot access parent directories: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	}
	return (cwd);
}
