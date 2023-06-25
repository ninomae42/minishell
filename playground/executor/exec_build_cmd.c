#include "executor.h"

void	connect_command(t_cmd *cmd, t_cmd_node *node)
{
	if (cmd->head == NULL)
		cmd->head = NULL;
	else
		cmd->tail->next = node;
	cmd->tail = node;
	cmd->num_of_commands++;
}

size_t	count_argc(t_ast_node *command_head)
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
		exit(EXIT_FAILURE);
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

bool	is_builtin(char *command_name);

void	build_simple_command(t_cmd_node *command, t_env *env)
{
	command->argc = count_argc(command->node);
	command->argv = set_argv(command->node, command->argc);
	command->environ = env_list_to_environ(env);
	if (is_builtin(command->argv[0]))
		command->is_builtin = true;
	prepare_redirect(command);
}

t_cmd	*build_command(t_ast *ast, t_env *env)
{
	t_ast_node	*pipeline;
	t_cmd_node	*simple_command;
	t_cmd		*cmd;

	cmd = new_cmd();
	pipeline = ast->root;
	while (pipeline)
	{
		simple_command = new_cmd_node(pipeline->child->child);
		build_simple_command(simple_command, env);
		connect_command(cmd, simple_command);
		pipeline = pipeline->brother;
	}
	return (cmd);
}

