#include "tokenizer.h"

// copys token literal and create new token node
t_token	*duplicate_word(t_token *cur, t_token_type type, char *begin, char *end)
{
	char	*literal;

	literal = strndup(begin, end - begin);
	if (literal ==  NULL)
		return (NULL);
	cur = new_token(cur, type, literal);
	if (cur ==  NULL)
		return (NULL);
	return (cur);
}

// create a new token. and connect to current token node
t_token	*new_token(t_token *current, t_token_type type, char *literal)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	current->next = new;
	new->type = type;
	new->literal = literal;
	new->next = NULL;
	return (new);
}
