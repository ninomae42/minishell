#include "exec.h"

t_cmd_node	*new_cmd_node(t_ast_node *node)
{
	t_cmd_node	*cmd;

	cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (cmd == NULL)
		ft_fatal("malloc");
	cmd->node = node;
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->environ = NULL;
	cmd->binary_path = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	destroy_cmd_node(t_cmd_node *cmd)
{
	free(cmd->argv);
	free(cmd);
}

int	exec_cmd(t_ast *ast)
{
	int		status;

	(void)ast;
	status = 0;
	return (status);
}
