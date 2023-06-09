#include "minishell.h"

int	main(void)
{
	char	*line;

	rl_outstream = stderr;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
