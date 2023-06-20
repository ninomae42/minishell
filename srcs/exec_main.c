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
	cmd->redirect = new_redirect();
	cmd->pid = -1;
	cmd->pipe_read_fd = -1;
	cmd->pipe_write_fd = -1;
	return (cmd);
}

void	destroy_cmd_node(t_cmd_node *cmd)
{
	destroy_redirect(cmd->redirect);
	free(cmd->argv);
	free(cmd);
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		ft_fatal("malloc");
	cmd->head = NULL;
	cmd->tail = NULL;
	cmd->num_of_commands = 0;
	return (cmd);
}

void	cmd_add_command(t_cmd *cmd, t_ast_node *node)
{
	t_cmd_node	*command;

	command = new_cmd_node(node);
	if (cmd->head == NULL)
		cmd->head = command;
	else
		cmd->tail->next = command;
	cmd->tail = command;
	cmd->num_of_commands++;
}

t_cmd	*build_command(t_ast *ast)
{
	t_ast_node	*pipeline;
	t_ast_node	*simple_command;
	t_cmd		*cmd;

	if (ast == NULL || ast->root == NULL)
		return (NULL);
	pipeline = ast->root;
	cmd = new_cmd();
	while (pipeline != NULL)
	{
		simple_command = pipeline->child;
		cmd_add_command(cmd, simple_command->child);
		pipeline = pipeline->brother;
	}
	return (cmd);
}

int	set_argv_and_redirect(char **argv, t_ast_node *node, t_redirect *redirect)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			argv[i++] = node->literal;
		else if (exec_node_is_redirect(node))
		{
			if (r_set_redirect(redirect, node) < 0)
				return (-1);
		}
		node = node->brother;
	}
	argv[i] = NULL;
	return (0);
}


int	exec_simple_command(t_cmd_node *cmd)
{
	pid_t	pid;
	int		status;

	status = 0;
	cmd->argc = count_argc(cmd->node);
	cmd->argv = alloc_argv(cmd->argc);
	if (set_argv_and_redirect(cmd->argv, cmd->node, cmd->redirect) < 0)
	{
		destroy_cmd_node(cmd);
		return (1);
	}
	cmd->environ = environ;
	pid = fork();
	if (pid < 0)
	{
		err_perror(errno);
		return (1);
	}
	if (pid == 0)
	{
		if (r_do_redirect(cmd->redirect) < 0)
			exit(EXIT_FAILURE);
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

void	exec_simple_command_child(t_cmd_node *cmd)
{
	cmd->argc = count_argc(cmd->node);
	cmd->argv = alloc_argv(cmd->argc);
	if (set_argv_and_redirect(cmd->argv, cmd->node, cmd->redirect) < 0)
	{
		destroy_cmd_node(cmd);
		exit(EXIT_FAILURE);
	}
	cmd->environ = environ;
	if (r_do_redirect(cmd->redirect) < 0)
		exit(EXIT_FAILURE);
	cmd->binary_path = cmd_get_binary_path(cmd->argv[0]);
	if (cmd->binary_path == NULL)
		exit(127);
	if (execve(cmd->binary_path, cmd->argv, cmd->environ) < 0)
	{
		err_perror(errno);
		exit(EXIT_FAILURE);
	}
}

#define PIPE_READ 0
#define PIPE_WRITE 1
#define PIPE_READ_WRITE 2

void	exec_open_pipe(t_cmd_node *command)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		ft_fatal("pipe");
	command->pipe_read_fd = pipe_fd[0];
	command->pipe_write_fd = pipe_fd[1];
}

void	exec_close_pipe(t_cmd_node *command)
{
	close(command->pipe_read_fd);
	close(command->pipe_write_fd);
}

void	exec_set_pipe_state(t_cmd_node *current, t_cmd_node *prev)
{
	if (current == prev)
		current->pipe_mode = PIPE_WRITE;
	else if (current->next == NULL)
		current->pipe_mode = PIPE_READ;
	else
		current->pipe_mode = PIPE_READ_WRITE;
}

void	exec_connect_pipes(t_cmd_node *current, t_cmd_node *prev)
{
	if (current->pipe_mode == PIPE_WRITE)
	{
		dup2(current->pipe_write_fd, STDOUT_FILENO);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ_WRITE)
	{
		dup2(prev->pipe_read_fd, STDIN_FILENO);
		dup2(current->pipe_write_fd, STDOUT_FILENO);
		exec_close_pipe(prev);
		exec_close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_READ)
	{
		dup2(prev->pipe_read_fd, STDIN_FILENO);
		exec_close_pipe(prev);
	}
}

int	exec_pipeline(t_cmd *cmd)
{
	t_cmd_node	*prev;
	t_cmd_node	*current;

	current = cmd->head;
	prev = current;
	while (current != NULL)
	{
		exec_set_pipe_state(current, prev);
		if (current->next != NULL)
			exec_open_pipe(current);
		current->pid = fork();
		if (current->pid == 0)
		{
			// do child process
			exec_connect_pipes(current, prev);
			exec_simple_command_child(current);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (prev != current)
				exec_close_pipe(prev);
			prev = current;
			current = current->next;
		}
	}
	// TODO: waitの仕方もっといい感じにする
	size_t	i = 0;
	int		status = 0;
	while (i < cmd->num_of_commands)
	{
		wait(&status);
		i++;
	}
	return (WEXITSTATUS(status));
}

int	exec_command(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (1 < cmd->num_of_commands)
		status = exec_pipeline(cmd);
	else
		status = exec_simple_command(cmd->head);
	return (status);
}

int	exec_cmd(t_ast *ast)
{
	int		status;
	t_cmd	*cmd;

	status = 0;
	cmd = build_command(ast);
	if (cmd == NULL)
		return (1);
	status = exec_command(cmd);
	printf("exec_cmd_finished: %d\n", status);
	return (status);
}
