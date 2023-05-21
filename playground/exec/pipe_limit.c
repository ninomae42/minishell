#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

#define UPMOST 65536
#define OVER 65537

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	int	pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);

	pid = fork();
	if (pid != 0)
	{
		close(pipe_fd[WRITE]);
		puts("parent proc");
		int	status;
		wait(&status);
		close(pipe_fd[READ]);
		printf("status: %d\n", status);
	}
	else
	{
		puts("child proc start");
		close(pipe_fd[READ]);
		size_t	i = 0;
		while (i < OVER)
		{
			write(pipe_fd[WRITE], "a", sizeof(char));
			i++;
		}
		close(pipe_fd[WRITE]);
		puts("child proc end");
		exit(EXIT_SUCCESS);
	}
}
