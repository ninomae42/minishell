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

bool	is_operator_chars(char c)
{
	if (c != '\0' && strchr(OPERATOR_CHARACTERS, c) != NULL)
		return (true);
	return (false);
}

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}
