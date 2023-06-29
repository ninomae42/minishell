/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:00:18 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:00:19 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(char **argv)
{
	size_t	i;
	bool	need_space;
	bool	need_newline;

	i = 1;
	need_newline = true;
	if (argv[1] != NULL && ft_strcmp(argv[1], "-n") == 0)
	{
		i++;
		need_newline = false;
	}
	need_space = false;
	while (argv[i])
	{
		if (need_space)
			ft_putchar_fd(' ', STDOUT_FILENO);
		need_space = true;
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
	}
	if (need_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
