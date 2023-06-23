#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"
#include "exec.h"
#include "ft_path.h"
#include "env.h"

int	main(void)
{
	int		status;
	char	*line;
	t_token	*token;
	t_ast	*ast;

	rl_outstream = stderr;
	status = 0;
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
		token = tokenize(line);
		token_print(token);
		ast = parse(token);
		puts("");
		ast_print(ast);
		status = exec_cmd(ast);
		ast_destroy(ast);
		token_destroy(token);
		free(line);
	}
	exit(status);
}
