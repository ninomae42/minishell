#include "exec.h"

int	check_state(void);

static void	heredoc_readline_loop(char *delimiter, int dest_fd)
{
	char	*line;

	rl_event_hook = check_state;
	rl_done = 0;
	g_env->signo = 0;
	g_env->is_readline_interrupted = false;
	while (true)
	{
		line = readline("> ");
		if (line == NULL || g_env->is_readline_interrupted
			|| ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, dest_fd);
		free(line);
	}
	rl_event_hook = NULL;
}

int	read_heredoc(char *delimiter)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		err_fatal(errno);
	heredoc_readline_loop(delimiter, pipe_fd[1]);
	close(pipe_fd[1]);
	if (g_env->is_readline_interrupted)
	{
		close(pipe_fd[0]);
		return (-1);
	}
	return (pipe_fd[0]);
}
