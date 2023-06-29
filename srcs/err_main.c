/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:21 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:22 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_err.h"

void	err_puterr(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
}

void	ft_fatal(char *func_name)
{
	perror(func_name);
	exit(EXIT_FAILURE);
}

void	err_perror(int err_no)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putendl_fd(strerror(err_no), STDERR_FILENO);
}

void	err_fatal(int err_no)
{
	err_perror(err_no);
	exit(EXIT_FAILURE);
}

void	err_perror_with_path(int err_no, char *path)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err_no), STDERR_FILENO);
}
