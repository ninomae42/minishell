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
const char	*path = {"/bin/cat"};
char *const	argument[] = {"cat", "./input.txt", NULL};
char *const	argument2[] = {"cat", NULL};

void	create_proc(size_t proc_id)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perr_exit("fork");
	if (pid == 0)
	{
		printf("[%zu] proc_id: %d start\n", proc_id, getpid());
		if (proc_id != 1)
		{
			if (execve(path, argument, environ) == -1)
				perr_exit("execve");
		}
		else
		{
			// if (execve("", argument, environ) == -1)
			if (execve(path, argument2, environ) == -1)
				perr_exit("execve");
		}
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	size_t	i = 0;
	size_t	proc_num = 3;
	while (i < proc_num)
	{
		create_proc(i);
		i++;
	}

	int	status = 0;
	i = 0;
	while (i < proc_num)
	{
		pid_t	waitprocid = waitpid(0, &status, 0);
		printf("waitpid: %d, status: %d\n", waitprocid, WEXITSTATUS(status));
		if (waitprocid == -1)
			perror("waitpid");
		i++;
	}
	printf("parent: last exit status %d\n", WEXITSTATUS(status));
	exit(EXIT_SUCCESS);
}
