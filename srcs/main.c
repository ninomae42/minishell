#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"
#include "exec.h"
#include "ft_path.h"

int	main(void)
{
	int		status;
	char	*line;

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
		char	*path = path_get_executable(line);
		printf("main: %s\n", path);
		free(path);
		// t_token *token = tokenize(line);
		// // token_print(token);
		// t_ast	*ast = parse(token);
		// // ast_print(ast);
		// status = exec_cmd(ast);
		// ast_destroy(ast);
		// token_destroy(token);
		free(line);
	}
	exit(status);
}
