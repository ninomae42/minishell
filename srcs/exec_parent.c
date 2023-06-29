/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:03:24 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:03:25 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_builtin_in_parent(t_cmd_node *command)
{
	int	status;

	if (setup_redirects(command->redirects) < 0)
	{
		reset_redirect(command->redirects);
		return (EXIT_FAILURE);
	}
	status = execute_builtin(command->argv);
	reset_redirect(command->redirects);
	return (status);
}
