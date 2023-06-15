#include "exec.h"

static int	r_add_redirect_node(t_redirect *redirect, char *filename, int redirect_type)
{
	t_redirect_node	*node;

	node = new_redirect_node(filename, redirect_type);
	if (node == NULL)
		return (-1);
	if (redirect->head == NULL)
		redirect->head = node;
	else
		redirect->tail->next = node;
	redirect->tail = node;
	return (0);
}

int	r_set_redirect(t_redirect *redirect, t_ast_node *node)
{
	char	*filename;
	int		res;

	filename = node->child->literal;
	res = 0;
	if (node->kind == ND_REDIRECT_IN)
		res = r_add_redirect_node(redirect, filename, REDIRECT_IN);
	else if (node->kind == ND_REDIRECT_OUT)
		res = r_add_redirect_node(redirect, filename, REDIRECT_OUT);
	else if (node->kind == ND_REDIRECT_OUT_APPEND)
		res = r_add_redirect_node(redirect, filename, REDIRECT_OUT_APPEND);
	else
		;
	if (res < 0)
		return (-1);
	return (0);
}

bool	exec_node_is_redirect(t_ast_node *node)
{
	t_node_kind	kind;

	kind = node->kind;
	if (kind == ND_REDIRECT_IN || kind == ND_REDIRECT_OUT
		|| kind == ND_REDIRECT_OUT_APPEND
		|| kind == ND_REDIRECT_IN_HDOC)
		return (true);
	return (false);
}
