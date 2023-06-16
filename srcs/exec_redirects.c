#include "exec.h"

t_redirect	*new_redirect(void)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (redirect == NULL)
		ft_fatal("malloc");
	redirect->head = NULL;
	redirect->tail = NULL;
	redirect->need_dup_input = false;
	redirect->need_dup_output = false;
	redirect->default_in_fd = STDIN_FILENO;
	redirect->default_out_fd = STDIN_FILENO;
	return (redirect);
}

void	destroy_redirect(t_redirect *redirect)
{
	delete_redirect_node(redirect->head);
	free(redirect);
}
