/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:54 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:54 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (cmd == NULL)
		err_fatal(errno);
	cmd->head = NULL;
	cmd->tail = NULL;
	cmd->num_of_commands = 0;
	return (cmd);
}

t_cmd_node	*new_cmd_node(t_ast_node *node)
{
	t_cmd_node	*cmd;

	cmd = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (cmd == NULL)
		err_fatal(errno);
	cmd->node = node;
	cmd->argc = 0;
	cmd->argv = NULL;
	cmd->environ = NULL;
	cmd->binary_path = NULL;
	cmd->is_builtin = false;
	cmd->pid = -1;
	cmd->pipe_mode = PIPE_NONE;
	cmd->pipe_fd_read = STDIN_FILENO;
	cmd->pipe_fd_write = STDOUT_FILENO;
	cmd->redirects = NULL;
	cmd->next = NULL;
	return (cmd);
}
