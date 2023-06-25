#include "executor.h"
#include <readline/readline.h>
#include <readline/history.h>

void	ft_putendl_fd(char *s, int fd);

int	read_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[1]);
		free(line);
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

t_redirect	*new_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		exit(EXIT_FAILURE);
	redirect->head = NULL;
	redirect->tail = NULL;
	redirect->need_dup_input = true;
	redirect->stash_in_fd = STDIN_FILENO;
	redirect->need_dup_output = true;
	redirect->stash_out_fd = STDOUT_FILENO;
	return (redirect);
}

t_redirect_node	*new_redirect_node(int redirect_type)
{
	t_redirect_node	*node;

	node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (node == NULL)
		exit(EXIT_FAILURE);
	node->fd = -1;
	node->filename = NULL;
	if (node->filename == NULL)
		exit(EXIT_FAILURE);
	node->redirect_type = redirect_type;
	node->next = NULL;
	return (node);
}

void	reset_redirect(t_redirect *redirect)
{
	if (dup2(STDIN_FILENO, redirect->stash_in_fd) < 0)
		exit(EXIT_FAILURE);
	if (dup2(STDOUT_FILENO, redirect->stash_out_fd) < 0)
		exit(EXIT_FAILURE);
}

bool	is_redirect_node(t_ast_node *node)
{
	if (node->kind == ND_REDIRECT_IN || node->kind == ND_REDIRECT_OUT
		|| node->kind == ND_REDIRECT_IN_HDOC || node->kind == ND_REDIRECT_OUT_APPEND)
		return (true);
	return (false);
}

void	duplicate_redirect(t_redirect *redirect, t_ast_node *command)
{
	t_redirect_node	*node;
	// expand redirect node literal
	// if len(expanded litereal) > 2, then ambiguous redirect
	// be ware of expansions
	node = new_redirect_node(command->kind);
	if (command->kind == ND_REDIRECT_IN_HDOC)
	{
		node->fd = read_heredoc(command->literal);
	}
	else
	{
		node->filename = strdup(command->literal);
		if (node->filename == NULL)
			exit(EXIT_FAILURE);
	}
	if (redirect->head == NULL)
		redirect->head = node;
	else
		redirect->tail->next = node;
	redirect->tail = node;
}

void	prepare_redirect(t_cmd_node *command)
{
	t_redirect	*redirect;
	t_ast_node	*head;

	redirect = new_redirect();
	head = command->node;
	while (head)
	{
		if (is_redirect_node(head))
			duplicate_redirect(redirect, head);
		head = head->brother;
	}
	command->redirects = redirect;
}

int	open_redirect_file(char *filename, int redirect_type)
{
	int	fd;

	if (redirect_type == ND_REDIRECT_IN)
		fd = open(filename, O_RDONLY);
	else if (redirect_type == ND_REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, REDIRECT_FILE_MODE);
	else if (redirect_type == ND_REDIRECT_OUT_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, REDIRECT_FILE_MODE);
}

void	connect_stream(t_redirect *redirect, t_redirect_node *node)
{
	if (node->redirect_type == ND_REDIRECT_IN || node->redirect_type == ND_REDIRECT_IN_HDOC)
	{
		if (redirect->need_dup_input)
		{
			redirect->stash_in_fd = dup(STDIN_FILENO);
			if (redirect->stash_in_fd < 0)
				exit(EXIT_FAILURE);
			redirect->need_dup_input = false;
		}
		dup2(node->fd, STDIN_FILENO);
		close(node->fd);
	}
	else if (node->redirect_type == ND_REDIRECT_OUT || node->redirect_type == ND_REDIRECT_OUT_APPEND)
	{
		if (redirect->need_dup_output)
		{
			redirect->stash_out_fd = dup(STDOUT_FILENO);
			if (redirect->stash_out_fd < 0)
				exit(EXIT_FAILURE);
			redirect->need_dup_output = false;
		}
		dup2(node->fd, STDOUT_FILENO);
		close(node->fd);
	}
}

int	open_redirect(t_redirect *redirect, t_redirect_node *node)
{
	node->fd = open_redirect_file(node->filename, node->redirect_type);
	if (node->fd < 0)
	{
		perror("open");
		return (-1);
	}
	connect_stream(redirect, node);
}

int	setup_redirects(t_cmd_node *command)
{
	t_redirect_node	*r_node;

	r_node = command->redirects->head;
	while (r_node)
	{
		if (open_redirect(command->redirects, r_node) < 0)
			exit(EXIT_FAILURE);
		r_node = r_node->next;
	}
	return (0);
}

void	exec_command_child(t_cmd_node *command, t_cmd_node *prev)
{
	set_pipe_state(command, prev);
	open_pipe(command);
	command->pid = fork();
	if (command->pid < 0)
		exit(EXIT_FAILURE);
	if (command->pid == 0)
	{
		connect_pipes(command, prev);
		if (setup_redirects(command) < 0)
			exit(EXIT_FAILURE);

		// find binary path(if not builtin)
		if (command->is_builtin)
			exit(execute_builtin(command->argv));
		if (execve(command->binary_path, command->argv, command->environ) < 0)
			exit(EXIT_FAILURE);
	}
	if (prev != command)
		close_pipe(prev);
}

void	fork_childs(t_cmd_node *command, t_cmd_node *prev)
{
	while (command)
	{
		exec_command_child(command, prev);
		prev = command;
		command = command->next;
	}
}

int	execute_pipeline(t_cmd *cmd)
{
	size_t		i;
	pid_t		pid;
	int			status;

	status = 0;
	fork_childs(cmd->head, cmd->head);
	i = 0;
	while (i < cmd->num_of_commands)
	{
		pid = waitpid(0, &status, NULL);
		if (pid < 0)
			perror("waitpid");
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			status = 128 + WTERMSIG(status);
		i++;
	}
	return (status);
}

int	execute_command(t_cmd *cmd)
{
	int	status;

	status = 0;
	if (cmd->num_of_commands == 1 && cmd->head->is_builtin)
		status = execute_builtin_in_parent(cmd->head);
	else
		status = execute_pipeline(cmd);
	return (status);
}

void	destroy_cmd(t_cmd *cmd);

int	main(void)
{
	t_ast	*ast;
	t_cmd	*cmd;
	t_env	*env;
	int		status;

	cmd = build_command(ast, env);
	status = execute_command(cmd);
	destroy_cmd(cmd);
	printf("status: %d\n", status);
}




void	destroy_redirect_nodes(t_redirect_node *head)
{
	t_redirect_node	*next;

	while (head)
	{
		next = head->next;
		free(next);
		head = next;
	}
}

void	destroy_redirect(t_redirect *redirects)
{
	destroy_redirect_nodes(redirects->head);
	free(redirects);
}

void	destroy_single_command_node(t_cmd_node *node)
{
	destroy_redirect(node->redirects);
	free(node->argv);
	free(node->environ);
	free(node->binary_path);
}

void	destroy_command_nodes(t_cmd_node *head)
{
	t_cmd_node	*next;

	while (head)
	{
		next = head->next;
		destroy_single_command_node(head);
		head = next;
	}
}

void	destroy_cmd(t_cmd *cmd)
{
	destroy_command_nodes(cmd->head);
	free(cmd);
}
