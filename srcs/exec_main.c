#include "exec.h"

void	fork_child(t_cmd_node *current, t_cmd_node *prev)
{
	set_pipe_state(current, prev);
	open_pipe(current);
	current->pid = fork();
	if (current->pid < 0)
		err_fatal(errno);
	if (current->pid == 0)
	{
		set_execution_sighandlers();
		connect_pipes(current, prev);
		if (setup_redirects(current->redirects) < 0)
			exit(EXIT_FAILURE);
		if (current->is_builtin)
			exit(execute_builtin(current->argv));
		exec(current);
	}
	if (prev != current)
		close_pipe(prev);
}

void	exec_commands_in_child(t_cmd_node *current, t_cmd_node *prev)
{
	while (current)
	{
		fork_child(current, prev);
		prev = current;
		current = current->next;
	}
}

int	execute_pipeline(t_cmd *cmd)
{
	int		status;
	size_t	i;
	pid_t	pid;

	status = 0;
	exec_commands_in_child(cmd->head, cmd->head);
	i = 0;
	while (i < cmd->num_of_commands)
	{
		pid = waitpid(0, &status, 0);
		if (pid < 0)
			err_perror(errno);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
	return (status);
}

void	execute_command(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->num_of_commands == 1 && cmd->head && cmd->head->is_builtin)
		g_env->status = execute_builtin_in_parent(cmd->head);
	else
		g_env->status = execute_pipeline(cmd);
}
