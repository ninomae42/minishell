/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:03:35 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:03:36 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	set_pipe_state(t_cmd_node *current, t_cmd_node *prev)
{
	if (current == prev && current->next == NULL)
		current->pipe_mode = PIPE_NONE;
	else if (current == prev)
		current->pipe_mode = PIPE_WR;
	else if (current->next == NULL)
		current->pipe_mode = PIPE_RD;
	else
		current->pipe_mode = PIPE_RDWR;
}

void	open_pipe(t_cmd_node *command)
{
	int	pipe_fd[2];

	if (command->pipe_mode == PIPE_NONE || command->pipe_mode == PIPE_RD)
		return ;
	if (pipe(pipe_fd) < 0)
		err_fatal(errno);
	command->pipe_fd_read = pipe_fd[0];
	command->pipe_fd_write = pipe_fd[1];
}

void	close_pipe(t_cmd_node *command)
{
	close(command->pipe_fd_read);
	close(command->pipe_fd_write);
}

void	connect_pipes(t_cmd_node *current, t_cmd_node *prev)
{
	if (current->pipe_mode == PIPE_WR)
	{
		if (dup2(current->pipe_fd_write, STDOUT_FILENO) < 0)
			err_fatal(errno);
		close_pipe(current);
	}
	else if (current->pipe_mode == PIPE_RDWR)
	{
		if (dup2(prev->pipe_fd_read, STDIN_FILENO) < 0)
			err_fatal(errno);
		if (dup2(current->pipe_fd_write, STDOUT_FILENO) < 0)
			err_fatal(errno);
		close_pipe(current);
		close_pipe(prev);
	}
	else if (current->pipe_mode == PIPE_RD)
	{
		if (dup2(prev->pipe_fd_read, STDIN_FILENO) < 0)
			err_fatal(errno);
		close_pipe(prev);
	}
	else
		return ;
}
