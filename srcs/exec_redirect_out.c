#include "exec.h"

int	do_output_redirect(char *filename, t_redirect *redirect)
{
	int	outfile_fd;

	outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	if (backup_output_fd(redirect) < 0)
	{
		close(outfile_fd);
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		reset_output_redirect(redirect);
		close(outfile_fd);
		return (-1);
	}
	return (0);
}

int	do_output_redirect_append(char *filename, t_redirect *redirect)
{
	int	outfile_fd;

	outfile_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	if (backup_output_fd(redirect) < 0)
	{
		close(outfile_fd);
		return (-1);
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		reset_output_redirect(redirect);
		close(outfile_fd);
		return (-1);
	}
	return (0);
}

int	do_input_redirect(char *filename, t_redirect *redirect)
{
	int	infile_fd;

	infile_fd = open(filename, O_RDONLY);
	if (infile_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	if (backup_input_fd(redirect) < 0)
	{
		close(infile_fd);
		return (-1);
	}
	if (dup2(infile_fd, STDIN_FILENO) < 0)
	{
		reset_input_redirect(redirect);
		close(infile_fd);
		return (-1);
	}
	return (0);
}

int	set_output_redirect(t_ast_node *node, t_redirect *redirect)
{
	if (node->kind == ND_REDIRECT_OUT)
		return (do_output_redirect(node->child->literal, redirect));
	else
		return (do_output_redirect_append(node->child->literal, redirect));
}
