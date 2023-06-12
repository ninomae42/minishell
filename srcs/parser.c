#include "parser.h"

static void	parser_init_token(t_parser *parser);

t_parser	*new_parser(t_token *token)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	parser->token = token;
	parser->cur_tok = NULL;
	parser->peek_tok = NULL;
	parser->is_syntax_err = false;
	parser_init_token(parser);
	return (parser);
}

void	p_next_token(t_parser *parser)
{
	parser->cur_tok = parser->peek_tok;
	if (parser->peek_tok != NULL)
		parser->peek_tok = parser->peek_tok->next;
	else
		parser->peek_tok = NULL;
}

void	parser_destroy(t_parser *parser)
{
	free(parser);
}

static void	parser_init_token(t_parser *parser)
{
	parser->cur_tok = parser->token->head;
	parser->peek_tok = parser->cur_tok->next;
}
