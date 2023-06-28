#include "exec.h"

int	check_state(void);

int	read_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	g_env->is_readline_interrupted = false;
	if (pipe(pipe_fd) < 0)
		err_fatal(errno);
	rl_event_hook = check_state;
	rl_done = 0;
	g_env->signo = 0;
	while (true)
	{
		line = readline("> ");
		if (line == NULL || g_env->is_readline_interrupted
			|| ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	rl_event_hook = NULL;
	if (g_env->is_readline_interrupted)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
