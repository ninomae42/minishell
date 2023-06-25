#include "builtin.h"

bool	is_builtin(char *command_name)
{
	size_t		i;
	const char	*cmds[] = {
		"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};

	if (command_name == NULL)
		return (false);
	i = 0;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], command_name) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	execute_builtin(char **argv)
{
	if (ft_strcmp(argv[0], "echo") == 0)
		return (builtin_echo(argv));
	// if (ft_strcmp(argv[0], "cd") == 0)
	// 	return (builtin_cd(argv));
	// if (ft_strcmp(argv[0], "pwd") == 0)
	// 	return (builtin_pwd(argv));
	// if (ft_strcmp(argv[0], "export") == 0)
	// 	return (builtin_export(argv));
	// if (ft_strcmp(argv[0], "unset") == 0)
	// 	return (builtin_unset(argv));
	if (ft_strcmp(argv[0], "env") == 0)
		return (builtin_env(argv));
	// if (ft_strcmp(argv[0], "exit") == 0)
	// 	return (builtin_exit(argv));
	exit(EXIT_FAILURE);
}
