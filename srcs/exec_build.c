#include "exec.h"

static void		connect_command(t_cmd *cmd, t_cmd_node *node);
static void		build_simple_command(t_cmd_node *command);
static size_t	count_argc(t_ast_node *command_head);
static char		**set_argv(t_ast_node *command_head, size_t argc);

t_cmd	*build_command(t_ast *ast)
{
	t_ast_node	*pipeline;
	t_cmd_node	*simple_command;
	t_cmd		*command_root;

	if (ast == NULL)
		return (NULL);
	command_root = new_cmd();
	pipeline = ast->root;
	while (pipeline)
	{
		simple_command = new_cmd_node(pipeline->child->child);
		build_simple_command(simple_command);
		connect_command(command_root, simple_command);
		pipeline = pipeline->brother;
	}
	return (command_root);
}

static void	build_simple_command(t_cmd_node *command)
{
	command->argc = count_argc(command->node);
	command->argv = set_argv(command->node, command->argc);
	// command->environ = env_list_to_environ(g_env);
	if (command->argv[0] != NULL && is_builtin(command->argv[0]))
		command->is_builtin = true;
	else
		command->is_builtin = false;
	prepare_redirect(command);
}

static void	connect_command(t_cmd *cmd, t_cmd_node *node)
{
	if (cmd->head == NULL)
		cmd->head = node;
	else
		cmd->tail->next = node;
	cmd->tail = node;
	cmd->num_of_commands++;
}

static size_t	count_argc(t_ast_node *command_head)
{
	size_t	len;

	len = 0;
	while (command_head)
	{
		if (command_head->kind == ND_WORD)
			len++;
		command_head = command_head->brother;
	}
	return (len);
}

char	**set_argv(t_ast_node *command_head, size_t argc)
{
	char	**argv;
	size_t	i;

	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		err_fatal(errno);
	i = 0;
	while (command_head)
	{
		if (command_head->kind == ND_WORD)
			argv[i++] = command_head->literal;
		command_head = command_head->brother;
	}
	argv[i] = NULL;
	return (argv);
}
