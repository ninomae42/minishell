#include "tokenizer.h"

bool	is_argc_valid(int argc)
{
	if (argc == 2)
		return (true);
	return (false);
}

bool	is_meta_character(char c)
{
	if (c != '\0' && strchr(META_CHARACTERS, c) != NULL)
		return (true);
	return (false);
}

t_token_type	find_token_type(char c)
{
	if (c == ' ')
		return (TK_SPACE);
	if (c == '\t')
		return (TK_TAB);
	if (c == '\n')
		return (TK_NEWLINE);
	if (c == '|')
		return (TK_PIPE);
	if (c == '&')
		return (TK_AMP);
	if (c == ';')
		return (TK_SEMICOLON);
	if (c == '(')
		return (TK_LPAREN);
	if (c == ')')
		return (TK_RPAREN);
	if (c == '<')
		return (TK_LT);
	if (c == '>')
		return (TK_GT);
	return (TK_EOF);
}
