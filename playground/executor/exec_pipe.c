#include "executor.h"

void	set_pipe_state(t_cmd_node *current, t_cmd_node *prev)
{
	if (current == prev && current->next == NULL)
		current->pipe_mode = PIPE_NO_PIPE;
	else if (current == prev)
		current->pipe_mode = PIPE_WRITE;
	else if (current->next == NULL)
		current->pipe_mode = PIPE_READ;
	else
		current->pipe_mode = PIPE_READ_WRITE;
}

void	open_pipe(t_cmd_node *command)
{
	int	pipe_fd[2];

	if (command->pipe_mode == PIPE_NO_PIPE || command->pipe_mode == PIPE_READ)
		return ;
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	command->pipe_fd_read = pipe_fd[0];
	command->pipe_fd_write = pipe_fd[1];
}

void	close_pipe(t_cmd_node *command)
{
	close(command->pipe_fd_read);
	close(command->pipe_fd_write);
}

void	connect_pipes(t_cmd_node *current, t_cmd_node *prev)
{
	if (current->pipe_mode == PIPE_WRITE)
	{
		if (dup2(current->pipe_fd_write, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ_WRITE)
	{
		if (dup2(prev->pipe_fd_read, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		if (dup2(current->pipe_fd_write, STDOUT_FILENO) < 0)
			exit(EXIT_FAILURE);
		close_pipe(current);
		close_pipe(prev);
	}
	else if (current->pipe_mode == PIPE_READ)
	{
		if (dup2(prev->pipe_fd_read, STDIN_FILENO) < 0)
			exit(EXIT_FAILURE);
		close_pipe(prev);
	}
	else
		return ;
}

