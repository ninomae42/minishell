/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:00:49 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:00:49 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "expander.h"

t_env_node	**copy_env_entries(t_env *env)
{
	t_env_node	**env_array;
	t_env_node	*node;
	size_t		i;

	env_array = (t_env_node **)malloc(sizeof(t_env_node *) * (env->size));
	if (env_array == NULL)
		err_fatal(errno);
	node = env->head;
	i = 0;
	while (node)
	{
		env_array[i] = new_env_node(node->name, node->value, NULL);
		if (env_array[i] == NULL)
			err_fatal(errno);
		node = node->next;
		i++;
	}
	return (env_array);
}

void	dealloc_env_entries(t_env_node **nodes, size_t num_of_entries)
{
	size_t	i;

	i = 0;
	while (i < num_of_entries)
	{
		free(nodes[i]);
		i++;
	}
	free(nodes);
}

void	sort_env_entries(t_env_node **entries, size_t num_of_entries)
{
	size_t		i;
	size_t		j;
	t_env_node	*tmp;

	i = 0;
	while (i < num_of_entries - 1)
	{
		j = i + 1;
		while (j < num_of_entries)
		{
			if (ft_strcmp(entries[i]->name, entries[j]->name) > 0)
			{
				tmp = entries[i];
				entries[i] = entries[j];
				entries[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_node(t_env_node *node)
{
	char	*escaped_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->name, STDOUT_FILENO);
	if (node->value)
	{
		escaped_value = get_escaped_str(node->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	export_print(void)
{
	t_env_node	**env_array;
	size_t		i;

	if (g_env->size == 0)
		return (EXIT_SUCCESS);
	env_array = copy_env_entries(g_env);
	sort_env_entries(env_array, g_env->size);
	i = 0;
	while (i < g_env->size)
	{
		print_env_node(env_array[i]);
		i++;
	}
	dealloc_env_entries(env_array, g_env->size);
	return (EXIT_SUCCESS);
}
