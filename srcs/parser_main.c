#include "parser.h"

bool	p_is_pipeline(t_parser *p)
{
	if (p->cur_tok == NULL)
		return (false);
	if (p->cur_tok->kind == TK_PIPELINE)
		return (true);
	return (false);
}

t_ast_node	*parse_pipeline(t_parser *parser)
{
	t_ast_node	*node;
	t_ast_node	*cur;
	t_ast_node	*child;

	if (p_at_eof(parser))
		return (NULL);
	child = parse_simple_command(parser);
	node = new_ast_node(ND_PIPELINE, child, NULL, NULL);
	cur = node;
	while (!parser->is_syntax_err && !p_at_eof(parser) && p_is_pipeline(parser))
	{
		p_next_token(parser);
		if (!p_is_simple_command_element(parser))
		{
			err_put_parser_syntax_err(parser->cur_tok->literal);
			parser->is_syntax_err = true;
			break ;
		}
		child = parse_simple_command(parser);
		cur->brother = new_ast_node(ND_PIPELINE, child, NULL, NULL);
		cur = cur->brother;
	}
	return (node);
}

t_ast	*parse(t_token *token)
{
	t_parser	*parser;
	t_ast		*ast;

	if (token == NULL)
		return (NULL);
	parser = new_parser(token);
	ast = new_ast();
	ast->root = parse_pipeline(parser);
	if (parser->is_syntax_err)
	{
		ast_node_destroy(ast->root);
		ast->root = NULL;
		g_env->status = 258;
	}
	parser_destroy(parser);
	return (ast);
}
