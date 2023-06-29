/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:00:28 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:00:29 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	print_env_node(t_env_node *node)
{
	if (node->value == NULL)
		return ;
	ft_putstr_fd(node->name, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(node->value, STDOUT_FILENO);
}

int	builtin_env(char **argv)
{
	t_env_node	*head;

	(void)argv;
	head = g_env->head;
	while (head)
	{
		print_env_node(head);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
