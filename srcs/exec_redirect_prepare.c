#include "exec.h"

static void			duplicate_redirect(t_redirect *redirect, t_ast_node *command);
static t_redir_type	node_kind_to_redir_type(t_ast_node *node);
static bool			is_redirect_node(t_ast_node *node);

void	prepare_redirect(t_cmd_node *command)
{
	t_redirect	*redirect;
	t_ast_node	*node;

	redirect = new_redirect();
	node = command->node;
	while (node)
	{
		if (is_redirect_node(node))
			duplicate_redirect(redirect, node);
		node = node->brother;
	}
	command->redirects = redirect;
}

static void	duplicate_redirect(t_redirect *redirect, t_ast_node *command)
{
	t_redirect_node	*node;

	node = new_redirect_node(node_kind_to_redir_type(command));
	if (command->literal == NULL)
		return ;
	if (node->type == RDIR_HDOC)
	{
		// TODO: do expand delmiter literal
		node->fd = read_heredoc(command->literal);
	}
	else
	{
		node->filename = ft_strdup(command->literal);
		if (node->filename == NULL)
			err_fatal(errno);
	}
	if (redirect->head == NULL)
		redirect->head = node;
	else
		redirect->tail->next = node;
	redirect->tail = node;
}

static t_redir_type	node_kind_to_redir_type(t_ast_node *node)
{
	if (node->kind == ND_REDIRECT_IN)
		return (RDIR_IN);
	if (node->kind == ND_REDIRECT_IN_HDOC)
		return (RDIR_HDOC);
	if (node->kind == ND_REDIRECT_OUT)
		return (RDIR_OUT);
	return (RDIR_APPEND);
}

static bool	is_redirect_node(t_ast_node *node)
{
	t_node_kind	kind;

	if (node == NULL)
		return (false);
	kind = node->kind;
	if (kind == ND_REDIRECT_IN || kind == ND_REDIRECT_IN_HDOC
		|| kind == ND_REDIRECT_OUT || kind == ND_REDIRECT_OUT_APPEND)
		return (true);
	return (false);
}
