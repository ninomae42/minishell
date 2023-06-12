#include "parser.h"

bool	p_is_simple_command_element(t_parser *p)
{
	t_token_kind	kind;

	if (p->cur_tok == NULL)
		return (false);
	kind = p->cur_tok->kind;
	if (kind == TK_WORD
		|| kind == TK_REDIRECT_IN || kind == TK_REDIRECT_IN_HDOC
		|| kind == TK_REDIRECT_OUT|| kind == TK_REDIRECT_OUT_APPEND)
		return (true);
	return (false);
}

t_ast_node	*parse_word(t_parser *parser)
{
	t_ast_node	*node;

	node = new_ast_node(ND_WORD, NULL, NULL, parser->cur_tok->literal);
	p_next_token(parser);
	return (node);
}

t_ast_node	*parse_simple_command_elem(t_parser *parser)
{
	t_ast_node	*node;

	if (p_cur_is(parser, TK_WORD))
		node = parse_word(parser);
	else
		node = parse_redirect(parser);
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
	while (!parser->is_syntax_err && !p_at_eof(parser)
			&& p_is_simple_command_element(parser))
	{
		child->brother = parse_simple_command_elem(parser);
		child = child->brother;
	}
	if (parser->is_syntax_err)
	{
		ast_node_destroy(node);
		return (NULL);
	}
	return (node);
}
