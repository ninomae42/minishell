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
