#include "minishell.h"

extern char	**environ;

int	exec(char *input)
{
	const char	*filename = input;
	const char	*argv[] = {input, NULL};
	pid_t		pid;
	int			status;

	status = 0;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(filename, (char *const *)argv, environ) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		return (status);
	}
	return (status);
}

int	main(void)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		status = exec(line);
		free(line);
	}
	exit(status);
}
