#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void	*perr_exit(char *prog_name)
{
	perror(prog_name);
	exit(EXIT_FAILURE);
}

extern char **environ;

int	main(void)
{
	const char	*path1 = "/bin/cat";
	char *const argv1[] = {"cat", "input.txt", NULL};

	const char	*path2 = "/usr/bin/grep";
	char *const argv2[] = {"grep", "ft", NULL};

	int	pipe_fd[2];
	
	if (pipe(pipe_fd) < 0)
		perr_exit("pipe");

	pid_t	pid = fork();
	if (pid < 0)
		perr_exit("fork");
	if (pid == 0)
	{
		close(pipe_fd[READ]);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[WRITE]);
		execve(path1, argv1, environ);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[WRITE]);
		dup2(pipe_fd[READ], STDIN_FILENO);
		close(pipe_fd[READ]);
		wait(NULL);
		execve(path2, argv2, environ);
		puts("[parent] executed");
		exit(EXIT_FAILURE);
	}
}
