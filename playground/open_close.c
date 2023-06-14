#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILE_NAME "output_test"
#define FILE_NAME2 "output_test2"

int	main(void)
{
	int	fd1;
	int	fd2;

	fd1 = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	printf("file_name: %s fd: %d\n", FILE_NAME, fd1);
	// write(fd1, "hoge\n", sizeof(char) * 5);
	close(fd1);

	fd2 = open(FILE_NAME2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	printf("file_name2: %s fd2: %d\n", FILE_NAME2, fd2);
	// write(fd2, "hoge\n", sizeof(char) * 5);
	close(fd2);
}
