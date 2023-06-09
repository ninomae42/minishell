#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PIPE_FD_CAP 2
#define READ 0
#define WRITE 1
extern char	**environ;

void	*perr_exit(char *prog_name)
{
	perror(prog_name);
	exit(EXIT_FAILURE);
}

typedef struct s_cmd	t_cmd;
struct s_cmd{
	const char	*path;
	char *const *argv;
	char *const *environ;
	t_cmd		*next;
	int			infile_fd;
	int			outfile_fd;
	int			*pipe_fd;
};

t_cmd	*new_command(char *path, char *const *argv, char *const *envp)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		perr_exit("malloc");
	cmd->path = path;
	cmd->argv = argv;
	cmd->environ = envp;
	return (cmd);
}

const char	*path = {"/bin/cat"};
char *const	argument[] = {"cat", "./input.txt", NULL};
char *const	argument2[] = {"grep", "ft", NULL};

t_cmd	*create_command()
{
	t_cmd	*cmd1;
	t_cmd	*cmd2;

	cmd1 = new_command("/bin/cat", argument, environ);
	cmd2 = new_command("/usr/bin/grep", argument2, environ);

	cmd1->next = cmd2;
	cmd2->next = NULL;
	return (cmd1);
}

size_t	count_commands(t_cmd *command)
{
	size_t	cnt;

	cnt = 0;
	while (command != NULL)
	{
		cnt++;
		command = command->next;
	}
	return (cnt);
}

void	connect_pipes(int infile, int pipefd[2], int outfile)
{
	if (0 <= infile)
		dup2(infile, pipefd[READ]);
	if (0 <= outfile)
		dup2(outfile, pipefd[WRITE]);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
}

void	create_proc(t_cmd *command, int pipefd[PIPE_FD_CAP])
{
	pid_t	pid;

	if (command ==  NULL)
		return ;
	create_proc(command->next, pipefd);
	pid = fork();
	if (pid == -1)
		perr_exit("fork");
	if (pid == 0)
	{
		printf("proc_id: %d start\n", getpid());
		if (execve(command->path, command->argv, command->environ) == -1)
			perr_exit("execve");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_cmd	*cmd = create_command();
	size_t	cmd_cnt = count_commands(cmd);

	int	pipe_fd[PIPE_FD_CAP];
	if (pipe(pipe_fd))
		perr_exit("pipe");
	cmd->pipe_fd = pipe_fd;
	cmd->infile_fd = -1;
	cmd->outfile_fd = -1;
	create_proc(cmd, NULL);

	int	status = 0;
	size_t i = 0;
	while (i < cmd_cnt)
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

