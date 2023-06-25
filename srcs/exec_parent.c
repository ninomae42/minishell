#include "exec.h"

int	execute_builtin_in_parent(t_cmd_node *command)
{
	int	status;

	if (setup_redirects(command->redirects) < 0)
	{
		reset_redirect(command->redirects);
		return (EXIT_FAILURE);
	}
	status = execute_builtin(command->argv);
	reset_redirect(command->redirects);
	return (status);
}
