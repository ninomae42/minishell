#include "parser.h"

bool	p_at_eof(t_parser *parser)
{
	if (parser->cur_tok == NULL || parser->cur_tok->kind == TK_EOF)
		return (true);
	return (false);
}

bool	p_cur_is(t_parser *parser, t_token_kind kind)
{
	if (parser->cur_tok != NULL && parser->cur_tok->kind == kind)
		return (true);
	return (false);
}

bool	p_peek_is(t_parser *parser, t_token_kind kind)
{
	if (parser->peek_tok != NULL && parser->peek_tok->kind == kind)
		return (true);
	return (false);
}
