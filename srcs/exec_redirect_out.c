#include "exec.h"

int	do_redirect_internal(t_redirect_node *cur, t_redirect *redirect)
{
	int	type;

	type = cur->redirect_type;
	if (type == REDIRECT_IN)
	{
		if (redirect->need_dup_input && r_backup_in_fd(redirect) < 0)
			return (-1);
		if (dup2(cur->file_fd, STDIN_FILENO) < 0)
		{
			if (redirect->default_in_fd != STDIN_FILENO)
				r_reset_in_redirect(redirect);
			return (-1);
		}
	}
	else if (type == REDIRECT_OUT || type == REDIRECT_OUT_APPEND)
	{
		if (redirect->need_dup_output && r_backup_out_fd(redirect) < 0)
			return (-1);
		if (dup2(cur->file_fd, STDOUT_FILENO) < 0)
		{
			if (redirect->default_out_fd != STDOUT_FILENO)
				r_reset_out_redirect(redirect);
			return (-1);
		}
	}
	close(cur->file_fd);
	cur->file_fd = -1;
	return (0);
}

int	r_do_redirect(t_redirect *redirect)
{
	t_redirect_node	*node;

	node = redirect->head;
	while (node != NULL)
	{
		if (do_redirect_internal(node, redirect) < 0)
			return (-1);
		node = node->next;
	}
	return (0);
}
