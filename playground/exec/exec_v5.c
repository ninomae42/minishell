#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define PIPE_FD_CAP 2
#define READ 0
#define WRITE 1
extern char	**environ;

void	perror_exit(char *filename)
{
	perror(filename);
	exit(EXIT_FAILURE);
}

#define FIRST 0
#define MID 1
#define LAST 2

typedef struct s_cmd_node
{

	const char			*path;
	char *const 		*argv;
	char *const 		*environ;
	struct s_cmd_node	*next;
	int					infile;
	int					outfile;
	int					pipe_in;
	int					pipe_out;
	int					pipe_loc;

}	t_cmd_node;

size_t	count_cmd_node(t_cmd_node *cmd)
{
	size_t	cnt;

	cnt = 0;
	while (cmd != NULL)
	{
		cmd = cmd->next;
		cnt++;
	}
	return (cnt);
}

t_cmd_node	*new_cmd_node(const char *path, char *const *argv, char *const *environ, int pipe_loc)
{
	t_cmd_node	*node;

	node = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (node == NULL)
		return (NULL);
	node->path = path;
	node->argv = argv;
	node->environ = environ;
	node->infile = STDIN_FILENO;
	node->outfile = STDOUT_FILENO;
	node->pipe_loc = pipe_loc;
	node->next = NULL;
	return (node);
}

const char	*path = "/bin/cat";
char *const	argument[] = {"cat", "./input.txt", NULL};
char *const	argument2[] = {"cat", NULL};

t_cmd_node	*create_command(void)
{
	t_cmd_node	*cmd1;
	t_cmd_node	*cmd2;

	cmd1 = new_cmd_node(path, argument, environ, FIRST);
	cmd2 = new_cmd_node(path, argument2, environ, LAST);
	// cmd1->next = cmd2;
	// cmd2->next = NULL;

	cmd1->next = NULL;
	cmd2->next = cmd1;
	return (cmd2);
	// return (cmd1);
}

void	do_pipeline(t_cmd_node *cmd, int *prev_pipe_fd)
{
	int	pipe_fd[2];
	if (cmd == NULL)
		return ;

	if (cmd->next != NULL)
		if (pipe(pipe_fd) < 0)
			perror_exit("pipe");
	pid_t	pid = fork();
	if (pid == -1)
		perror_exit("fork");
	if (pid == 0)
	{
		printf("Child proc[%d], %s, %s\n", getpid(), cmd->path, cmd->argv[1]);
		if (prev_pipe_fd != NULL)
			printf("Child proc[%d], in: %d, out:%d\n", getpid(), prev_pipe_fd[0], prev_pipe_fd[1]);
		else
			printf("Child proc[%d], in: %d, out:%d\n", getpid(), pipe_fd[0], pipe_fd[1]);
		if (cmd->next != NULL)
			dup2(pipe_fd[READ], STDIN_FILENO);
		if (prev_pipe_fd != NULL)
			dup2(prev_pipe_fd[WRITE], STDOUT_FILENO);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		if (prev_pipe_fd != NULL)
		{
			close(prev_pipe_fd[READ]);
			close(prev_pipe_fd[WRITE]);
		}
		execve(cmd->path, cmd->argv, cmd->environ);
		perror_exit("execve");
	}
	else
	{
		do_pipeline(cmd->next, pipe_fd);
		close(pipe_fd[READ]);
		close(pipe_fd[WRITE]);
		if (prev_pipe_fd != NULL)
		{
			close(prev_pipe_fd[READ]);
			close(prev_pipe_fd[WRITE]);
		}
	}
}

int	main(void)
{
	t_cmd_node	*cmd;
	size_t	cmd_num;

	cmd = create_command();
	cmd_num = count_cmd_node(cmd);

	do_pipeline(cmd, NULL);

	size_t	i = 0;
	printf("parent is waiting for child procs\n");
	while (i < cmd_num)
	{
		int	status = 0;
		pid_t	pid = waitpid(0, &status, 0);
		if (pid == -1)
			perror("waitpid");
		printf("parent: child pid[%d] is exit with status: %d\n", pid, WEXITSTATUS(status));
		i++;
	}

	exit(EXIT_SUCCESS);
}
