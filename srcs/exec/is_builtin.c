#include "exec.h"

bool	is_builtin(char *filename)
{
	const char	*builtin[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	size_t	i;

	i = 0;
	while (builtin[i] != NULL)
	{
		if (strcmp(filename, builtin[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
