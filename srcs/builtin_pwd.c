#include "builtin.h"
char	*get_current_working_directory(void);

void	init_pwd(void)
{
	char	*pwd;
	char	*sys_cwd;

	pwd = env_get_value(g_env, "PWD");
	if (pwd == NULL)
	{
		sys_cwd = getcwd(NULL, 0);
		if (sys_cwd)
			env_set(g_env, "PWD", sys_cwd, 1);
		g_env->pwd = ft_strdup(sys_cwd);
		if (g_env->pwd == NULL)
			err_fatal(errno);
		free(sys_cwd);
	}
	else
	{
		g_env->pwd = ft_strdup(pwd);
		if (g_env->pwd == NULL)
			err_fatal(errno);
	}
	g_env->old_pwd = env_get_value(g_env, "OLDPWD");
	if (g_env->old_pwd != NULL)
	{
		g_env->old_pwd = ft_strdup(g_env->old_pwd);
		if (g_env->old_pwd == NULL)
			err_fatal(errno);
	}
}


int	builtin_pwd(char **argv)
{
	(void)argv;
	ft_putendl_fd(g_env->pwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
