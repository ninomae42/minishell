#include "exec.h"

#define PIPE_READ 0
#define PIPE_WRITE 1
#define PIPE_READ_WRITE 2

void	exec_set_pipe_state(t_cmd_node *current, t_cmd_node *prev)
{
	if (current == prev)
		current->pipe_mode = PIPE_WRITE;
	else if (current->next == NULL)
		current->pipe_mode = PIPE_READ;
	else
		current->pipe_mode = PIPE_READ_WRITE;
}

// this functions is called from PARENT process.
// if error occur, report error and return caller. caller must handle error properly.
int	exec_open_pipe(t_cmd_node *command)
{
	int	pipe_fd[2];

	if (ft_pipe(pipe_fd) < 0)
		return (1);
	command->pipe_read_fd = pipe_fd[0];
	command->pipe_write_fd = pipe_fd[1];
	return (0);
}

void	exec_close_pipe(t_cmd_node *command)
{
	close(command->pipe_read_fd);
	close(command->pipe_write_fd);
}

// this function is called inside the child process.
// if error occur, then report error and terminate child process.
void	exec_connect_pipes(t_cmd_node *current, t_cmd_node *prev)
{
	errno = 0;
	if (current->pipe_mode == PIPE_WRITE)
	{
		if (dup2(current->pipe_write_fd, STDOUT_FILENO) < 0)
			err_fatal(errno);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ_WRITE)
	{
		if (dup2(prev->pipe_read_fd, STDIN_FILENO) < 0)
			err_fatal(errno);
		if (dup2(current->pipe_write_fd, STDOUT_FILENO) < 0)
			err_fatal(errno);
		exec_close_pipe(prev);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ)
	{
		if (dup2(prev->pipe_read_fd, STDIN_FILENO) < 0)
			err_fatal(errno);
		exec_close_pipe(prev);
	}
}

int	exec_fork_procs(t_cmd_node *current, t_cmd_node *prev, t_env *env)
{
	while (current != NULL)
	{
		exec_set_pipe_state(current, prev);
		if (current->next != NULL && exec_open_pipe(current) < 0)
			return (1);
		current->pid = ft_fork();
		if (current->pid < 0)
			return (1);
		if (current->pid == 0)
		{
			exec_connect_pipes(current, prev);
			exec_simple_command_child(current, env);
			exit(EXIT_FAILURE);
		}
		if (prev != current)
			exec_close_pipe(prev);
		prev = current;
		current = current->next;
	}
	return (0);
}
