#include "exec.h"

size_t	count_argc(t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			i++;
		node = node->brother;
	}
	return (i);
}

char	**dup_argv(t_ast_node *node, size_t argc)
{
	char	**argv;
	size_t	i;

	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			argv[i++] = node->literal;
		node = node->brother;
	}
	argv[i] = NULL;
	return (argv);
}

void	reset_output_redirect(t_redirect *redirect)
{
	if (redirect->need_backup_out)
		return ;
	dup2(redirect->default_out_fd, STDOUT_FILENO);
	close(redirect->default_out_fd);
	redirect->default_out_fd = STDOUT_FILENO;
	redirect->need_backup_out = true;
}

int	do_redirect(t_redirect *redirect)
{
	redirect->default_out_fd = dup(redirect->default_out_fd);
	if (redirect->default_out_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	redirect->need_backup_out = false;
	return (0);
}

int	do_output_redirect(char *filename, t_redirect *redirect)
{
	int	outfile_fd;

	outfile_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	if (redirect->need_backup_out)
	{
		if (do_redirect(redirect) < 0)
		{
			close(outfile_fd);
			return (-1);
		}
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		reset_output_redirect(redirect);
		close(outfile_fd);
		return (-1);
	}
	close(outfile_fd);
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
	if (redirect->need_backup_out)
	{
		if (do_redirect(redirect) < 0)
		{
			close(outfile_fd);
			return (-1);
		}
	}
	if (dup2(outfile_fd, STDOUT_FILENO) < 0)
	{
		reset_output_redirect(redirect);
		close(outfile_fd);
		return (-1);
	}
	close(outfile_fd);
	return (0);
}

int	set_output_redirect(t_cmd *cmd, t_ast_node *node)
{
	if (node->kind == ND_REDIRECT_OUT)
		return (do_output_redirect(node->child->literal, &cmd->redirect));
	else
		return (do_output_redirect_append(node->child->literal, &cmd->redirect));
}

// int	set_output_redirect(t_cmd *cmd, t_ast_node *node)
// {
// 	int	out_fd;
//
// 	if (node->kind == ND_REDIRECT_OUT)
// 		out_fd = open(node->child->literal, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else
// 		out_fd = open(node->child->literal, O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	if (out_fd < 0)
// 	{
// 		err_perror(errno);
// 		return (-1);
// 	}
// 	dup2(out_fd, cmd->fd_out);
// 	close(out_fd);
// 	return (0);
// }

void	set_argv_and_redirect(t_cmd *cmd, t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			cmd->argv[i++] = node->literal;
		else if (node->kind == ND_REDIRECT_OUT || node->kind == ND_REDIRECT_OUT_APPEND)
			set_output_redirect(cmd, node);
		else if (node->kind == ND_REDIRECT_IN || node->kind == ND_REDIRECT_IN_HDOC)
			;
		node = node->brother;
	}
	cmd->argv[i] = NULL;
}
