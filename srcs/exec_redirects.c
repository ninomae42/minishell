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

int	backup_output_fd(t_redirect *redirect)
{
	int	backup_fd;

	backup_fd = dup(redirect->default_out_fd);
	if (backup_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	redirect->default_out_fd = backup_fd;
	redirect->need_dup_output = false;
	return (0);
}

void	reset_output_redirect(t_redirect *redirect)
{
	if (redirect->need_dup_output)
		return ;
	if (dup2(redirect->default_out_fd, STDOUT_FILENO) < 0)
		err_perror(errno);
	if (close(redirect->default_out_fd) < 0)
		err_perror(errno);
	redirect->default_out_fd = STDOUT_FILENO;
	redirect->need_dup_output = true;
}

int	backup_input_fd(t_redirect *redirect)
{
	int	backup_fd;

	backup_fd = dup(redirect->default_in_fd);
	if (backup_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	redirect->default_in_fd = backup_fd;
	redirect->need_dup_input = false;
	return (0);
}

void	reset_input_redirect(t_redirect *redirect)
{
	if (redirect->need_dup_input)
		return ;
	if (dup2(redirect->default_in_fd, STDIN_FILENO) < 0)
		err_perror(errno);
	if (close(redirect->default_in_fd) < 0)
		err_perror(errno);
	redirect->default_in_fd = STDIN_FILENO;
	redirect->need_dup_input = true;
}

