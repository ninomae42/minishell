#include "exec.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->environ = NULL;
	cmd->exec_path = NULL;
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	free(cmd->argv);
	free(cmd);
}
