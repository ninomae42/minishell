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


void	err_is_directory(char *path)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(ERR_IS_DIRECTORY, STDERR_FILENO);
}

void	err_command_not_found(char *command_name)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(command_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(COMMAND_NOT_FOUND, STDERR_FILENO);
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

// bash: $foo: ambiguous redirect
void	err_ambiguous_redirect(char *filename)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(ERR_AMBIGUOUS_REDIRECT, STDERR_FILENO);
}
