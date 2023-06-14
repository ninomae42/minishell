#include "exec.h"

extern char	**environ;

void	set_argv_and_redirect(t_cmd *cmd, t_ast_node *node);

t_cmd	*build_simple_command(t_ast_node *node)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	cmd->argc = count_argc(node);
	// cmd->argv = dup_argv(node, cmd->argc);
	cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc + 1));
	set_argv_and_redirect(cmd, node);
	cmd->environ = environ;
	cmd->exec_path = cmd_get_binary_path(cmd->argv[0]);
	return (cmd);
}

t_cmd	*make_cmd(t_ast *ast)
{
	t_cmd	*cmd;

	if (ast->root->kind == ND_SIMPLE_COMMAND)
		cmd = build_simple_command(ast->root->child);
	else
		cmd = NULL;
	return (cmd);
}

int	exec_simple_command(t_cmd *cmd);

int	exec_cmd(t_ast *ast)
{
	int		status;
	t_cmd	*cmd;

	status = 0;
	cmd = make_cmd(ast);
	if (cmd->exec_path == NULL)
		return (127);
	status = exec_simple_command(cmd);
	return (status);
}
