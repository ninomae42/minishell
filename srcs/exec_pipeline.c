#include "exec.h"

#define PIPE_READ 0
#define PIPE_WRITE 1
#define PIPE_READ_WRITE 2

void	exec_open_pipe(t_cmd_node *command)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		ft_fatal("pipe");
	command->pipe_read_fd = pipe_fd[0];
	command->pipe_write_fd = pipe_fd[1];
}

void	exec_close_pipe(t_cmd_node *command)
{
	close(command->pipe_read_fd);
	close(command->pipe_write_fd);
}

void	exec_set_pipe_state(t_cmd_node *current, t_cmd_node *prev)
{
	if (current == prev)
		current->pipe_mode = PIPE_WRITE;
	else if (current->next == NULL)
		current->pipe_mode = PIPE_READ;
	else
		current->pipe_mode = PIPE_READ_WRITE;
}

void	exec_connect_pipes(t_cmd_node *current, t_cmd_node *prev)
{
	if (current->pipe_mode == PIPE_WRITE)
	{
		dup2(current->pipe_write_fd, STDOUT_FILENO);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ_WRITE)
	{
		dup2(prev->pipe_read_fd, STDIN_FILENO);
		dup2(current->pipe_write_fd, STDOUT_FILENO);
		exec_close_pipe(prev);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ)
	{
		dup2(prev->pipe_read_fd, STDIN_FILENO);
		exec_close_pipe(prev);
	}
}

int	exec_pipeline(t_cmd *cmd)
{
	t_cmd_node	*prev;
	t_cmd_node	*current;

	current = cmd->head;
	prev = current;
	while (current != NULL)
	{
		exec_set_pipe_state(current, prev);
		if (current->next != NULL)
			exec_open_pipe(current);
		current->pid = fork();
		// must handle fork error. if error occurs terminate all pre-allocated processes
		if (current->pid == 0)
		{
			// do child process
			exec_connect_pipes(current, prev);
			exec_simple_command_child(current);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev != current)
				exec_close_pipe(prev);
			prev = current;
			current = current->next;
		}
	}
	// TODO: waitの仕方もっといい感じにする
	size_t	i = 0;
	int		status = 0;
	while (i < cmd->num_of_commands)
	{
		wait(&status);
		i++;
	}
	return (WEXITSTATUS(status));
}
