#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	int	fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR, S_IRGRP, S_IROTH);
	write(fd, argv[2], strlen(argv[2]));
	close(fd);
	return (0);
}
