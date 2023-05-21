#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*perr_exit(char *prog_name)
{
	perror(prog_name);
	exit(EXIT_FAILURE);
}

#define READ 0
#define WRITE 1

extern char	**environ;

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	const char	*path = {"/bin/cat"};
	char *const	argument[] = {"cat", "./input.txt", NULL};

	pid_t	pid;
	pid = fork();
	if (pid != 0)
	{
		// do parent process
		puts("Parent process start");
		int	status;
		wait(&status);
		printf("child exit status: %d\n", WEXITSTATUS(status));
	}
	else
	{
		puts("Child process start");
		// do child process
		if (execve(path, argument, environ) == -1)
			perr_exit("execve");
	}
	exit(EXIT_SUCCESS);
}
