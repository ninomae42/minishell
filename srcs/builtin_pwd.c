#include "builtin.h"

char	*get_sys_cwd_path(char *caller);

void	init_pwd(void)
{
	char	*sys_cwd;
	char	*dup;

	sys_cwd = get_sys_cwd_path("shell-init");
	printf("pwd: %s\n", sys_cwd);
	if (sys_cwd != NULL)
	{
		dup = ft_strdup(sys_cwd);
		if (dup == NULL)
			err_fatal(errno);
		env_set(g_env, "PWD", dup, 1);
		free(sys_cwd);
		free(dup);
	}
	env_set(g_env, "OLDPWD", NULL, 1);
}

int	builtin_pwd(char **argv)
{
	char	*cwd;

	(void)argv;
	cwd = get_sys_cwd_path("pwd");
	if (cwd == NULL)
		return (EXIT_FAILURE);
	else
		ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (EXIT_SUCCESS);
}
