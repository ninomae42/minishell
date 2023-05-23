#include "tokenizer.h"
#include "parser/parser.h"
#include "exec/exec.h"

bool	is_argc_valid(int argc)
{
	return (argc == 2);
}

int	main(int argc, char **argv)
{
	t_token	*token;
	bool	is_error;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	is_error = false;
	token = tokenize(argv[1], &is_error);
	print_token(token);
	puts("=====");
	t_node	*ast = parse(token);
	dealloc_token(token);
	print_ast_pre_order(ast);
	int status = exec_command(ast);
	exit(status);
}
