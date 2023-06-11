#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (s[len] && len < maxlen)
		len++;
	return (len);
}

char	*ft_strndup(char *s, size_t len)
{
	char	*res;
	size_t	alloc_size;

	alloc_size = ft_strnlen(s, len) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (res == NULL)
		return (NULL);
	strlcpy(res, s, alloc_size);
	return (res);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		exit(EXIT_FAILURE);

	char	*libc = strndup(argv[1], atoi(argv[2]));
	char	*ft = ft_strndup(argv[1], atoi(argv[2]));
	printf("libc: %s\n", libc);
	printf("ft: %s\n", ft);
	exit(EXIT_SUCCESS);
}
