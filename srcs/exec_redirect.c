#include "exec.h"

t_redirect	*new_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		err_fatal(errno);
	redirect->head = NULL;
	redirect->tail = NULL;
	redirect->need_dup_input = true;
	redirect->fd_in_dup = STDIN_FILENO;
	redirect->need_dup_output = true;
	redirect->fd_out_dup = STDOUT_FILENO;
	return (redirect);
}

t_redirect_node	*new_redirect_node(t_redir_type type)
{
	t_redirect_node	*node;

	node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (node == NULL)
		err_fatal(errno);
	node->type = type;
	node->fd = -1;
	node->filename = NULL;
	node->next = NULL;
	return (node);
}

void	reset_redirect(t_redirect *redirect)
{
	if (dup2(STDIN_FILENO, redirect->fd_in_dup) < 0)
		err_fatal(errno);
	if (dup2(STDOUT_FILENO, redirect->fd_out_dup) < 0)
		err_fatal(errno);
}
