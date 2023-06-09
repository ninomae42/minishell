#include "exec.h"

extern char	**environ;

t_cmd	*make_simple_command(t_ast_node *node)
{
	t_cmd	*cmd;

	cmd = new_cmd();
	cmd->argc = count_argc(node);
	cmd->argv = dup_argv(node, cmd->argc);
	cmd->environ = environ;
	cmd->exec_path = cmd->argv[0];
	return (cmd);
}

t_cmd	*make_cmd(t_ast *ast)
{
	t_cmd	*cmd;

	if (ast->root->kind == ND_SIMPLE_COMMAND)
		cmd = make_simple_command(ast->root->child);
	else
		cmd = NULL;
	return (cmd);
}

int	exec_cmd(t_ast *ast)
{
	pid_t	pid;
	int		status;
	t_cmd	*cmd;

	status = 0;
	cmd = make_cmd(ast);
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
		cmd_destroy(cmd);
	}
	return (status);
}
