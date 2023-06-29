/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:03:54 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:03:54 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expander.h"

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
			return (-1);
		}
		connect_stream(redirects, r_node);
		r_node = r_node->next;
	}
	return (0);
}

static bool	is_redirect_ambiguous(char *filename)
{
	if (*filename == '\0')
		return (true);
	while (*filename)
	{
		if (*filename == ' ' || *filename == '\t' || *filename == '\n')
			return (true);
		filename++;
	}
	return (false);
}

static int	open_redirect_file(char *filename, t_redir_type type)
{
	char	*expanded_filename;
	int		fd;

	fd = -1;
	if (filename == NULL)
		errno = EINVAL;
	errno = 0;
	expanded_filename = expand_word(filename);
	if (is_redirect_ambiguous(expanded_filename))
		err_ambiguous_redirect(filename);
	else if (type == RDIR_IN)
		fd = open(expanded_filename, O_RDONLY);
	else if (type == RDIR_OUT)
		fd = open(expanded_filename, O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	else if (type == RDIR_APPEND)
		fd = open(expanded_filename, O_WRONLY | O_CREAT | O_APPEND, FILE_MODE);
	if (fd < 0 && errno != 0)
		err_perror_with_path(errno, filename);
	free(expanded_filename);
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
