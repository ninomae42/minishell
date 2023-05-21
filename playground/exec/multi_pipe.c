#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

void	*perr_exit(char *prog_name)
{
	perr_exit(prog_name);
	exit(EXIT_FAILURE);
}

// cat input.txt | grep ft | grep str

extern char **environ;

int	main(void)
{
	const char	*path1 = "/bin/cat";
	char *const argv1[] = {"cat", "input.txt", NULL};

	const char	*path2 = "/usr/bin/grep";
	char *const argv2[] = {"grep", "ft", NULL};

	const char	*path3 = "/usr/bin/grep";
	char *const argv3[] = {"grep", "len", NULL};

	int	pipe_fd[2];
	int	pipe_fd2[2];

	if (pipe(pipe_fd) < 0)
		perr_exit("pipe");
	if (pipe(pipe_fd2) < 0)
		perr_exit("pipe");
	

	pid_t	pid1 = fork();
	if (pid1 < 0)
		perr_exit("fork");
	if (pid1 == 0)
	{
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		close(pipe_fd2[READ]);
		close(pipe_fd2[WRITE]);
		execve(path1, argv1, environ);
	}
	else
	{
		pid_t	pid2 = fork();
		if (pid2 < 0)
			perr_exit("fork");
		if (pid2 == 0)
		{
			dup2(pipe_fd[READ], STDIN_FILENO);
			dup2(pipe_fd2[WRITE], STDOUT_FILENO);
			close(pipe_fd[READ]);
			close(pipe_fd[WRITE]);
			close(pipe_fd2[READ]);
			close(pipe_fd2[WRITE]);
			execve(path2, argv2, environ);
			exit(EXIT_FAILURE);
		}
		else
		{
			close(pipe_fd[WRITE]);
			dup2(pipe_fd2[READ], STDIN_FILENO);
			close(pipe_fd[READ]);
			close(pipe_fd2[READ]);
			close(pipe_fd2[WRITE]);
			execve(path3, argv3, environ);
			puts("[parent] executed");
			exit(EXIT_FAILURE);
		}

	}
}