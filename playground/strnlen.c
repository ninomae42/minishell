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

int	main(int argc, char **argv)
{
	if (argc != 3)
		exit(EXIT_FAILURE);
	printf("libc: %zu\n", strnlen(argv[1], atoi(argv[2])));
	printf("ft: %zu\n", ft_strnlen(argv[1], atoi(argv[2])));
}
