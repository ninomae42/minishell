#include "exec.h"

int	ft_fork(void)
{
	pid_t	pid;

	errno = 0;
	pid = fork();
	if (pid < 0)
		err_perror(errno);
	return (pid);
}

int	ft_pipe(int filedes[2])
{
	int	res;

	errno = 0;
	res = pipe(filedes);
	if (res < 0)
		err_perror(errno);
	return (res);
}

int	ft_kill(pid_t pid, int sig)
{
	int	res;

	errno = 0;
	res = kill(pid, sig);
	if (res < 0)
		err_perror(errno);
	return (res);
}
