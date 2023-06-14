#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#define F1 "out1"
#define F2 "out2"
#define F3 "out3"

char	*argv[] = {"echo", "hogehoge", NULL};

int	main(void)
{
	int	original = STDOUT_FILENO;
	int	backup = STDOUT_FILENO;

	int	fd1 = open(F1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	int	fd2 = open(F2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fprintf(stderr, "orig: %d, backup: %d, fd1: %d, fd2: %d\n", original, backup, fd1, fd2);

	backup = dup(original);
	fprintf(stderr, "orig: %d, backup: %d, fd1: %d, fd2: %d\n", original, backup, fd1, fd2);
	dup2(fd1, original);
	fprintf(stderr, "orig: %d, backup: %d, fd1: %d, fd2: %d\n", original, backup, fd1, fd2);
	close(fd1);
	fprintf(stderr, "orig: %d, backup: %d, fd1: %d, fd2: %d\n", original, backup, fd1, fd2);
	dup2(fd2, original);
	fprintf(stderr, "orig: %d, backup: %d, fd1: %d, fd2: %d\n", original, backup, fd1, fd2);
	execv("/bin/echo", argv);
}
