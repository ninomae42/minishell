#include "exec.h"
extern char **environ;

size_t	count_argc(t_node *commands)
{
	size_t	count;

	count = count_words(commands);
	return (count);
}

void	set_argv(size_t argc, char **argv, t_node *commands)
{
	size_t	i;

	i = 0;
	while (i < argc)
	{
		argv[i] = commands->word;
		commands = commands->brother;
		i++;
	}
	argv[i] = NULL;
}

t_cmd_node	*new_cmd_node()
{
	t_cmd_node	*node;

	node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (node == NULL)
		perror_exit("malloc");
	memset(node, 0, sizeof(t_cmd_node));
	return (node);
}

t_cmd_node	*simple_command_node(t_node *ast)
{
	t_cmd_node	*cmd;

	cmd = new_cmd_node();
	cmd->environ = environ;
	cmd->argc = count_argc(ast->child->brother);
	cmd->argv = (char **)malloc(sizeof(char *) * (cmd->argc + 1));
	if (cmd->argv == NULL)
		perror_exit("malloc");
	set_argv(cmd->argc, cmd->argv, ast->child->brother);
	cmd->filename = cmd->argv[0];
	return (cmd);
}

int	exec_simple_command(t_node *ast)
{
	pid_t	pid;
	int		status;
	t_cmd_node	*cmd;

	cmd = simple_command_node(ast);
	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		if (execve(cmd->filename, cmd->argv, cmd->environ) < 0)
			perror_exit("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		status = 0;
		wait(&status);
		printf("parent: child exited with status: %d\n", WEXITSTATUS(status));
		return (status);
	}
}

int	exec_command(t_node *ast)
{
	int	status;

	status = exec_simple_command(ast);
	return (status);
}
