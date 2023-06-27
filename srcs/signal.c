#include "minishell.h"

static void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", sizeof(char));
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_normal_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		err_fatal(errno);
	}
}

void	set_execution_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR
		|| signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		err_fatal(errno);
	}
}

void	set_heredoc_sighandlers(void)
{
	// TODO: SIG_INT must break readline loop;
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, SIG_IGN) == SIG_ERR)
	{
		err_fatal(errno);
	}
}
