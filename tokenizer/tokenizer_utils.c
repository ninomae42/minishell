#include "tokenizer.h"

bool	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_meta_character(char c)
{
	return (c != '\0' && strchr(META_CHARACTERS, c) != NULL);
}

bool	is_operator_charcter(char c)
{
	return (c != '\0' && strchr(OPERATOR_CHARACTERS, c) != NULL);
}
