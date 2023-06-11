#include "ft_path.h"

void	dir_print(char **dirs)
{
	size_t	i;

	i = 0;
	while (dirs[i])
	{
		printf("%s\n", dirs[i]);
		i++;
	}
}

size_t	dir_len(char **dirs)
{
	size_t	len;

	len = 0;
	while (dirs[len])
		len++;
	return (len);
}
