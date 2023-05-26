#include "environ.h"

char	*env_entry_new_str(const char *name, const char *value)
{
	size_t	alloc_size;
	char	*res;

	alloc_size = ft_strlen(name) + 1 + ft_strlen(value) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, name, alloc_size);
	ft_strlcat(res, "=", alloc_size);
	ft_strlcat(res, value, alloc_size);
	return (res);
}
