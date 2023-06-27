#include "builtin.h"

void	set_pwd_value(void)
{
	g_env->pwd = env_get_value(g_env, "PWD");
	if (g_env->pwd != NULL)
	{
		g_env->pwd = ft_strdup(g_env->pwd);
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
