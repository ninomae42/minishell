#include "tokenizer.h"

t_token	*new_token(t_token *cur, t_token_type type, char *literal)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->type = type;
	token->literal = literal;
	token->next = NULL;
	cur->next = token;
	return (token);
}

void	skip_blanks(char **begin)
{
	const char	*current = *begin;

	while (*current && is_blank(*current))
		current++;
	*begin = (char *)current;
}
