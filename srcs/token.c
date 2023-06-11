#include "tokenizer.h"

t_token	*new_token(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token->head = NULL;
	token->tail = NULL;
	token->size = 0;
	return (token);
}

t_token_node	*new_token_node(t_token_kind kind, char *literal)
{
	t_token_node	*node;

	node = (t_token_node *)malloc(sizeof(t_token_node));
	if (node == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->kind = kind;
	node->literal = literal;
	node->next = NULL;
	return (node);
}

void	token_destroy(t_token *token)
{
	t_token_node	*cur;
	t_token_node	*next;

	cur = token->head;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->kind == TK_WORD)
			free(cur->literal);
		free(cur);
		cur = next;
	}
	free(token);
}

void	token_print(t_token *token)
{
	t_token_node	*cur;

	cur = token->head;
	while (cur != NULL)
	{
		printf("tk_kind: %s, literal: %s\n",
			token_kind_to_str(cur->kind), cur->literal);
		cur = cur->next;
	}
}
