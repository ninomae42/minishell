#include "parser.h"

t_ast	*parse(t_token *token)
{
	t_parser	*parser;
	t_ast		*ast;

	parser = new_parser(token);
	ast = new_ast();
	ast->root = parse_simple_command(parser);
	parser_destroy(parser);
	return (ast);
}
