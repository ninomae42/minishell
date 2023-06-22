#include "exec.h"

void	exec_terminate_procs(t_cmd_node *current)
{
	while (current != NULL && 0 < current->pid)
	{
		ft_kill(current->pid, SIGTERM);
		current = current->next;
	}
}

int	exec_wait_procs(t_cmd *commands)
{
	size_t	i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < commands->num_of_commands)
	{
		errno = 0;
		pid = waitpid(0, &status, 0);
		if (pid < 0)
			err_perror(errno);
		i++;
	}
	return (WEXITSTATUS(status));
}
