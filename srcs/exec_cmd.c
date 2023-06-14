#include "exec.h"

void	init_redirect(t_redirect *redirect)
{
	redirect->need_backup_in = true;
	redirect->default_in_fd = STDIN_FILENO;
	redirect->need_backup_out = true;
	redirect->default_out_fd = STDOUT_FILENO;
}

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
	init_redirect(&(cmd->redirect));
	return (cmd);
}

void	cmd_destroy(t_cmd *cmd)
{
	free(cmd->argv);
	free(cmd);
}
