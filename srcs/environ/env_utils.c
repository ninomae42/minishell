#include "environ.h"

bool	is_env_name_valid(const char *name)
{
	if (name == NULL || *name == '\0')
		return (false);
	if (strchr(name, '=') != NULL)
		return (false);
	return (true);
}
