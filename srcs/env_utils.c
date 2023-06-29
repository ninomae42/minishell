/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:02 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:02 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_env_node	*env_find_node(t_env *env, char *name)
{
	t_env_node	*current;

	if (!env_is_name_valid(name) || env == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	current = env->head;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	env_is_name_valid(char *name)
{
	if (name == NULL || *name == '\0')
		return (false);
	if (ft_strchr(name, '=') != NULL)
		return (false);
	return (true);
}

char	*make_pair_str(char *name, char *value)
{
	size_t	alloc_size;
	char	*str;

	if (value == NULL)
		return (NULL);
	alloc_size = ft_strlen(name) + ft_strlen(value) + 2;
	str = (char *)malloc(sizeof(char) * alloc_size);
	if (str == NULL)
		err_fatal(errno);
	ft_strlcpy(str, name, alloc_size);
	ft_strlcat(str, "=", alloc_size);
	ft_strlcat(str, value, alloc_size);
	return (str);
}

size_t	count_exported_strs(t_env *env)
{
	size_t		num_of_strs;
	t_env_node	*head;

	head = env->head;
	num_of_strs = 0;
	while (head)
	{
		if (head->pair_str != NULL)
			num_of_strs++;
		head = head->next;
	}
	return (num_of_strs);
}

char	**env_list_to_environ(t_env *env)
{
	char		**strs;
	t_env_node	*node;
	size_t		i;

	strs = (char **)malloc(sizeof(char *) * (count_exported_strs(env) + 1));
	if (strs == NULL)
		err_fatal(errno);
	i = 0;
	node = env->head;
	while (node != NULL)
	{
		if (node->pair_str != NULL)
			strs[i++] = node->pair_str;
		node = node->next;
	}
	strs[i] = NULL;
	return (strs);
}
