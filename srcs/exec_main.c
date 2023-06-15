#include "exec.h"

extern char **environ;

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

size_t	count_argc(t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			i++;
		node = node->brother;
	}
	return (i);
}

char	**alloc_argv(size_t argc)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		ft_fatal("malloc");
	return (argv);
}

void	set_argv(char **argv, t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			argv[i] = node->literal;
		i++;
		node = node->brother;
	}
	argv[i] = NULL;
}

int	exec_simple_command(t_cmd_node *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	cmd->argc = count_argc(cmd->node);
	cmd->argv = alloc_argv(cmd->argc);
	set_argv(cmd->argv, cmd->node);
	cmd->environ = environ;
	pid = fork();
	if (pid < 0)
	{
		err_perror(errno);
		return (1);
	}
	if (pid == 0)
	{
		cmd->binary_path = cmd_get_binary_path(cmd->argv[0]);
		if (cmd->binary_path == NULL)
			exit(127);
		if (execve(cmd->binary_path, cmd->argv, cmd->environ) < 0)
		{
			err_perror(errno);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		destroy_cmd_node(cmd);
	}
	return (WEXITSTATUS(status));
}

int	exec_cmd(t_ast *ast)
{
	int		status;
	t_cmd_node	*cmd;

	status = 0;
	cmd = build_command(ast);
	status = exec_simple_command(cmd);
	printf("exec_cmd_finished: %d\n", status);
	return (status);
}
