#include "ft_err.h"

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

// bash: $foo: ambiguous redirect
void	err_ambiguous_redirect(char *filename)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(ERR_AMBIGUOUS_REDIRECT, STDERR_FILENO);
}
