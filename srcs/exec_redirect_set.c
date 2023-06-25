#include "exec.h"

static int	open_redirect_file(char *filename, t_redir_type type);
static void	backup_std_stream(t_redirect *redirect, int target);
static void	connect_stream(t_redirect *redirect, t_redirect_node *node);

int	setup_redirects(t_redirect *redirects)
{
	t_redirect_node	*r_node;

	r_node = redirects->head;
	while (r_node)
	{
		if (r_node->type == RDIR_IN
			|| r_node->type == RDIR_OUT || r_node->type == RDIR_APPEND)
			r_node->fd = open_redirect_file(r_node->filename, r_node->type);
		if (r_node->fd < 0)
		{
			err_perror_with_path(errno, r_node->filename);
			return (-1);
		}
		connect_stream(redirects, r_node);
		r_node = r_node->next;
	}
	return (0);
}

static int	open_redirect_file(char *filename, t_redir_type type)
{
	int	fd;

	fd = -1;
	if (filename == NULL)
		errno = EINVAL;
	else if (type == RDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (type == RDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, RDIR_FILE_MODE);
	else if (type == RDIR_APPEND)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, RDIR_FILE_MODE);
	return (fd);
}

static void	connect_stream(t_redirect *redirect, t_redirect_node *node)
{
	if (node->type == RDIR_IN || node->type == RDIR_HDOC)
	{
		if (redirect->need_dup_input)
			backup_std_stream(redirect, STDIN_FILENO);
		if (dup2(node->fd, STDIN_FILENO) < 0)
			err_fatal(errno);
	}
	else
	{
		if (redirect->need_dup_output)
			backup_std_stream(redirect, STDOUT_FILENO);
		if (dup2(node->fd, STDOUT_FILENO) < 0)
			err_fatal(errno);
	}
	close(node->fd);
}

static void	backup_std_stream(t_redirect *redirect, int target)
{
	if (target == STDIN_FILENO)
	{
		redirect->fd_in_dup = dup(STDIN_FILENO);
		if (redirect->fd_in_dup < 0)
			err_fatal(errno);
		redirect->need_dup_input = false;
	}
	else if (target == STDOUT_FILENO)
	{
		redirect->fd_out_dup = dup(STDOUT_FILENO);
		if (redirect->fd_out_dup < 0)
			err_fatal(errno);
		redirect->need_dup_output = false;
	}
}
