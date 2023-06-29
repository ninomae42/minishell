/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:01:55 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:01:56 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env	*new_env(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		err_fatal(errno);
	env->size = 0;
	env->head = NULL;
	env->tail = NULL;
	env->status = 0;
	return (env);
}

t_env_node	*new_env_node(char *name, char *value, char *pair_str)
{
	t_env_node	*node;

	node = (t_env_node *)malloc(sizeof(t_env_node));
	if (node == NULL)
		err_fatal(errno);
	node->name = name;
	node->value = value;
	node->pair_str = pair_str;
	node->next = NULL;
	return (node);
}

void	destroy_env(t_env *env)
{
	if (env == NULL)
		return ;
	destroy_env_nodes(env->head);
	free(env);
}

void	destroy_env_node(t_env_node *node)
{
	free(node->name);
	free(node->value);
	free(node->pair_str);
	free(node);
}

void	destroy_env_nodes(t_env_node *head)
{
	t_env_node	*next;

	while (head != NULL)
	{
		next = head->next;
		destroy_env_node(head);
		head = next;
	}
}
