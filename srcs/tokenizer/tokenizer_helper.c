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

void	dealloc_token(t_token *head)
{
	t_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		free(head);
		head = tmp->next;
	}
}

char	*token_type2str(t_token_type type)
{
	if (type == TK_WORD)
		return ("TK_WORD");
	if (type == TK_OPERATOR)
		return ("TK_OPERATOR");
	if (type == TK_EOF)
		return ("TK_EOF");
	return ("UNKNOWN");
}

void	print_token(t_token *token)
{
	while (token != NULL)
	{
		printf("type: %s, literal: %s\n", token_type2str(token->type), token->literal);
		token = token->next;
	}
}
