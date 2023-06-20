#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_pipe
{
	int	pipe_in;
	int	pipe_out;
}	t_pipe;

char	*cmd1[] = {"echo", "hogehoge", NULL};
char	*cmd2[] = {"cat", NULL};
char	*cmd3[] = {"cat", NULL};
t_pipe	pipe1;
t_pipe	pipe2;

int	main(void)
{
	int		pipe_fd[2];
	pid_t	pid;

	pipe(pipe_fd);
	pipe1.pipe_in = pipe_fd[0];
	pipe1.pipe_out = pipe_fd[1];
	pid = fork();
	if (pid == 0)
	{
		// dup2(pipe_in, STDIN_FILENO);
		dup2(pipe1.pipe_out, STDOUT_FILENO);
		close(pipe1.pipe_in);
		close(pipe1.pipe_out);
		execvp("echo", cmd1);
		exit(EXIT_SUCCESS);
	}

	pipe(pipe_fd);
	pipe2.pipe_in = pipe_fd[0];
	pipe2.pipe_out = pipe_fd[1];
	pid = fork();
	if (pid == 0)
	{
		dup2(pipe1.pipe_in, STDIN_FILENO);
		dup2(pipe2.pipe_out, STDOUT_FILENO);
		close(pipe1.pipe_in);
		close(pipe1.pipe_out);
		close(pipe2.pipe_in);
		close(pipe2.pipe_out);
		execvp("cat", cmd2);
		exit(EXIT_SUCCESS);
	}
	close(pipe1.pipe_in);
	close(pipe1.pipe_out);

	pid = fork();
	if (pid == 0)
	{
		dup2(pipe2.pipe_in, STDIN_FILENO);
		// dup2(pipe_out, STDOUT_FILENO);
		close(pipe2.pipe_in);
		close(pipe2.pipe_out);
		execvp("cat", cmd3);
		exit(EXIT_SUCCESS);
	}
	close(pipe2.pipe_in);
	close(pipe2.pipe_out);
	wait(NULL);
	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);
}
