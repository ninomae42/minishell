#include "parser.h"

t_ast_node	*parse_simple_command_elem(t_parser *parser)
{
	t_ast_node	*node;

	if (p_cur_is(parser, TK_WORD))
	{
		node = new_ast_node(ND_WORD, NULL, NULL, parser->cur_tok->literal);
		p_next_token(parser);
	}
	else
		node = NULL;
	return (node);
}

t_ast_node	*parse_simple_command(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*child;

	if (p_at_eof(parser))
		return (NULL);
	child = parse_simple_command_elem(parser);
	node = new_ast_node(ND_SIMPLE_COMMAND, child, NULL, NULL);
	while (!p_at_eof(parser) && p_cur_is(parser, TK_WORD))
	{
		child->brother = parse_simple_command_elem(parser);
		child = child->brother;
	}
	return (node);
}
