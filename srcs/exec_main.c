/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:03:18 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/30 22:50:05 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	fork_child(t_cmd_node *current, t_cmd_node *prev)
{
	set_pipe_state(current, prev);
	open_pipe(current);
	current->pid = fork();
	if (current->pid < 0)
		err_fatal(errno);
	if (current->pid == 0)
	{
		set_execution_sighandlers();
		connect_pipes(current, prev);
		if (setup_redirects(current->redirects) < 0)
			exit(EXIT_FAILURE);
		if (current->is_builtin)
			exit(execute_builtin(current->argv));
		current->binary_path = current->argv[0];
		current->environ = env_list_to_environ(g_env);
		exec(current->binary_path, current->argv, current->environ);
	}
	if (prev != current)
		close_pipe(prev);
}

void	exec_commands_in_child(t_cmd_node *current, t_cmd_node *prev)
{
	while (current)
	{
		fork_child(current, prev);
		prev = current;
		current = current->next;
	}
}

void	wait_child_procs(t_cmd *cmd, int *last_status)
{
	int			status;
	pid_t		last_pid;
	pid_t		pid;
	t_cmd_node	*node;

	node = cmd->head;
	while (node && node->next)
		node = node->next;
	last_pid = node->pid;
	while (true)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1 && errno == ECHILD)
			break ;
		else if (pid == -1)
			err_perror(errno);
		if (pid == last_pid && WIFEXITED(status))
			*last_status = WEXITSTATUS(status);
		else if (pid == last_pid && WIFSIGNALED(status))
			*last_status = 128 + WTERMSIG(status);
	}
}

int	execute_pipeline(t_cmd *cmd)
{
	int		status;

	status = 0;
	exec_commands_in_child(cmd->head, cmd->head);
	wait_child_procs(cmd, &status);
	return (status);
}

void	execute_command(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	if (cmd->num_of_commands == 1 && cmd->head && cmd->head->is_builtin)
		g_env->status = execute_builtin_in_parent(cmd->head);
	else
		g_env->status = execute_pipeline(cmd);
}
