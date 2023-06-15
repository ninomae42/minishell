#include "exec.h"

int	r_backup_out_fd(t_redirect *redirect)
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

void	r_reset_out_redirect(t_redirect *redirect)
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

int	r_backup_in_fd(t_redirect *redirect)
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

void	r_reset_in_redirect(t_redirect *redirect)
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
