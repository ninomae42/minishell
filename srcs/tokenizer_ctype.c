#include "tokenizer.h"

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '|'
			// || c == '(' || c == ')'
			|| c == '<' || c == '>');
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_redirect_character(char c)
{
	return (c == '<' || c == '>');
}

bool	is_pipeline_character(char c)
{
	return (c == '|');
}
