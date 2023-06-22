#include "exec.h"

int	exec_pipeline(t_cmd *cmd)
{
	int	status;

	if (exec_fork_procs(cmd->head, cmd->head) < 0)
	{
		// TODO: error handling. report error and deallocate resourses
		exec_terminate_procs(cmd->head);
		destroy_cmd(cmd);
		return (1);
	}
	status = exec_wait_procs(cmd);
	return (status);
}
