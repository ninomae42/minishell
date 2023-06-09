#include "tokenizer.h"

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '|' || c == '&' || c == ';'
			|| c == '(' || c == ')'
			|| c == '<' || c == '>');
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}
