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

t_cmd_node	*build_command(t_ast *ast)
{
	t_ast_node	*node;
	t_cmd_node	*cmd;

	node = ast->root;
	cmd = new_cmd_node(node->child);
	return (cmd);
}

int	exec_cmd(t_ast *ast)
{
	int		status;
	t_cmd_node	*cmd;

	status = 0;
	cmd = build_command(ast);
	return (status);
}
