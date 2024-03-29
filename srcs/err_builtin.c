/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:08 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:08 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_err.h"

// bash: unset: `1fuga': not a valid identifier

void	err_identifier(char *command_name, char *identifier)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(command_name, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putendl_fd(ERR_IDENT_INVALID, STDERR_FILENO);
}

void	err_builtin_exit(char *err_msg, char *arg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd("exit: ", STDERR_FILENO);
	if (arg != NULL)
	{
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(err_msg, STDERR_FILENO);
}

void	err_builtin_cd_perror_with_path(int err_no, char *path)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_CD_PREFIX, STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(err_no), STDERR_FILENO);
}

void	err_builtin_cd(char *err_msg)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_CD_PREFIX, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
}

void	err_env_name_not_valid(char *env_str)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putchar_fd('`', STDERR_FILENO);
	ft_putstr_fd(env_str, STDERR_FILENO);
	ft_putchar_fd('\'', STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(ERR_INVALID_ENV_IDENT, STDERR_FILENO);
}
