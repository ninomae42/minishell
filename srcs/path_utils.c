#include "ft_path.h"

bool	path_is_contain_slash(char *path)
{
	if (*path != '\0' && ft_strchr(path, '/') != NULL)
		return (true);
	return (false);
}

bool	path_is_directory(char *path)
{
	struct stat	st;

	errno = 0;
	if (stat(path, &st) < 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

bool	path_is_exist(char *path)
{
	errno = 0;
	if (access(path, F_OK) < 0)
		return (false);
	return (true);
}
