/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:06:43 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:06:44 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	g_env->signo = sig;
}

int	hook_signal_event(void)
{
	if (g_env->signo == SIGINT)
	{
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
		g_env->is_readline_interrupted = true;
		rl_done = 1;
		rl_event_hook = NULL;
		return (0);
	}
	return (0);
}
