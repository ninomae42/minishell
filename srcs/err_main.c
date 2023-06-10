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
