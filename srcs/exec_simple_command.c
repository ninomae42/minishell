#include "exec.h"

extern char	**environ;

void	reset_output_redirect(t_redirect *redirect);

int	exec_simple_command(t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (cmd->exec_path == NULL)
		return (127);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		cmd_destroy(cmd);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd->exec_path, cmd->argv, cmd->environ) < 0)
			perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		reset_output_redirect(&cmd->redirect);
		cmd_destroy(cmd);
	}
	return (status);
}
