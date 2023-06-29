#include "minishell.h"

static void	sigint_handler(int sig);

void	set_normal_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		err_fatal(errno);
	}
}

static void	sigint_handler(int sig)
{
	// printf("signal handler\n");
	g_env->signo = sig;
}

int	hook_signal_event(void)
{
	// printf("signal event\n");
	if (g_env->signo == SIGINT)
	{
		// g_env->signo = 0;
		// printf("signal event\n");
		write(STDOUT_FILENO, "\n", sizeof(char));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return (0);
	}
	return (0);
}

void	set_execution_sighandlers(void)
{
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR
		|| signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		err_fatal(errno);
	}
}

int	heredoc_event_hook(void)
{
	if (g_env->signo == SIGINT)
	{
		// printf("check state\n");
		g_env->is_readline_interrupted = true;
		rl_done = 1;
		rl_event_hook = NULL;
		return (0);
	}
	return (0);
}
