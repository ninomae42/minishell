#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"
#include "exec.h"

extern char		**environ;
extern t_env	*g_env;

void	init_minishell(void)
{
	rl_outstream = stderr;
	g_env = new_env();
	env_load_environ(g_env, environ);
}

void	cleanup_environment(void)
{
	destroy_env(g_env);
}

void	interpret(char *line)
{
	t_token	*token;
	t_ast	*ast;
	t_cmd	*cmd;

	token = tokenize(line);
	token_print(token);
	puts("");
	ast = parse(token);
	ast_print(ast);
	cmd = build_command(ast);
	execute_command(cmd);
	ast_destroy(ast);
	token_destroy(token);
}

int	main(void)
{
	char	*line;

	init_minishell();
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		interpret(line);
		free(line);
	}
	cleanup_environment();
	exit(g_env->status);
}
