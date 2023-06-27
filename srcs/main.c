#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"
#include "expander.h"
#include "exec.h"

extern char		**environ;
t_env			*g_env;
void	init_pwd(void);

void	init_minishell(void)
{
	rl_outstream = stderr;
	g_env = new_env();
	env_load_environ(g_env, environ);
	init_pwd();
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

	printf("===tokenize start===\n");
	token = tokenize(line);
	token_print(token);
	printf("===parse start===\n");
	ast = parse(token);
	ast_print(ast);
	printf("===expand start===\n");
	expand(ast);
	ast_print(ast);
	printf("===build command start===\n");
	cmd = build_command(ast);
	printf("===execute command start===\n");
	execute_command(cmd);
	destroy_cmd(cmd);
	ast_destroy(ast);
	token_destroy(token);
}

int	main_loop(void)
{
	char	*line;

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
