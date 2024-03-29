/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:05:25 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:05:25 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "exec.h"

extern char		**environ;
t_env			*g_env;

void	init_minishell(void)
{
	extern int	_rl_echo_control_chars;

	rl_outstream = stderr;
	_rl_echo_control_chars = 0;
	g_env = new_env();
	g_env->signo = 0;
	rl_signal_event_hook = hook_signal_event;
	env_load_environ(g_env, environ);
	init_pwd();
	set_normal_sighandlers();
}

void	cleanup_environment(void)
{
	destroy_env(g_env);
	rl_clear_history();
}

void	interpret(char *line)
{
	t_token	*token;
	t_ast	*ast;
	t_cmd	*cmd;

	token = tokenize(line);
	ast = parse(token);
	if (ast && ast->root)
	{
		expand(ast);
		cmd = build_command(ast);
		execute_command(cmd);
		destroy_cmd(cmd);
	}
	ast_destroy(ast);
	token_destroy(token);
}

int	main_loop(void)
{
	char	*line;

	while (true)
	{
		g_env->signo = 0;
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		interpret(line);
		free(line);
	}
	return (g_env->status);
}

int	main(void)
{
	int	status;

	init_minishell();
	status = main_loop();
	cleanup_environment();
	exit(status);
}

// void	interpret(char *line)
// {
// 	t_token	*token;
// 	t_ast	*ast;
// 	t_cmd	*cmd;
//
// 	// printf("===tokenize start===\n");
// 	token = tokenize(line);
// 	// token_print(token);
// 	// printf("===parse start===\n");
// 	ast = parse(token);
// 	// ast_print(ast);
// 	// printf("===expand start===\n");
// 	if (ast && ast->root)
// 	{
// 		expand(ast);
// 		// ast_print(ast);
// 		// printf("===build command start===\n");
// 		cmd = build_command(ast);
// 		// printf("===execute command start===\n");
// 		execute_command(cmd);
// 		destroy_cmd(cmd);
// 	}
// 	ast_destroy(ast);
// 	token_destroy(token);
// }
