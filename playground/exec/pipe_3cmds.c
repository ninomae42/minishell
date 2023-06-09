#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	perror_exit(char *func_name)
{
	perror(func_name);
	exit(EXIT_FAILURE);
}

extern char	**environ;

int	main(void)
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int		pipe_fd[2];
	int		pipe_fd2[2];
	const char	*path1 = "/bin/cat";
	const char	*path2 = "/usr/bin/grep";

	char	*arg1_1 = "cat";
	char	*arg1_2 = "./input.txt";
	char	*arg2_1 = "cat";
	char	*arg3_1 = "grep";
	char	*arg3_2 = "ft";
	char *const	arg1[] = {arg1_1, arg1_2, NULL};
	char *const	arg2[] = {arg2_1, NULL};
	char *const	arg3[] = {arg3_1, arg3_2 , NULL};

	if (pipe(pipe_fd))
		perror_exit("pipe");
	pid1 = fork();
	if (pid1 == 0)
	{
		// do first command
		// puts("child 1");
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve(path1, arg1, environ);
		perror_exit("execve");
	}

	if (pipe(pipe_fd2))
		perror_exit("pipe");
	pid2 = fork();
	if (pid2 == 0)
	{
		// do second command
		// puts("child 2");
		dup2(pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd2[1], STDOUT_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd2[0]);
		close(pipe_fd2[1]);
		execve(path1, arg2, environ);
		perror_exit("execve");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	pid3 = fork();
	if (pid3 == 0)
	{
		// do third command
		// puts("child 3");
		dup2(pipe_fd2[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(pipe_fd2[0]);
		close(pipe_fd2[1]);
		execve(path2, arg3, environ);
		perror_exit("execve");
	}
	close(pipe_fd2[0]);
	close(pipe_fd2[1]);

	puts("parent is waiting");
	int	status;
	wait(&status);
	wait(&status);
	wait(&status);
	exit(EXIT_SUCCESS);
}
