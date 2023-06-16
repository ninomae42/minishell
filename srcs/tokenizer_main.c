#include "tokenizer.h"

static t_token_node	*t_next_token(t_tokenizer *tokenizer);
static void			connect_node(t_token *token, t_token_node *node);
static void			t_skip_whitespace(t_tokenizer *tokenizer);

t_token	*tokenize(char *input)
{
	t_tokenizer		*tokenizer;
	t_token			*token;
	t_token_node	*node;

	tokenizer = new_tokenizer(input);
	token = new_token();
	while (!t_at_eof(tokenizer))
	{
		t_skip_whitespace(tokenizer);
		node = t_next_token(tokenizer);
		if (node == NULL)
			break ;
		connect_node(token, node);
	}
	node = new_token_node(TK_EOF, NULL);
	connect_node(token, node);
	tokenizer_destroy(tokenizer);
	return (token);
}

static t_token_node	*t_next_token(t_tokenizer *tokenizer)
{
	t_token_node	*node;

	if (t_at_eof(tokenizer))
		return (NULL);
	else if (t_is_redirect(tokenizer))
		node = t_tokenize_redirect(tokenizer);
	else if (t_is_pipeline(tokenizer))
		node = t_tokenize_pipeline(tokenizer);
	else
		node = t_tokenize_word(tokenizer);
	return (node);
}

static void	t_skip_whitespace(t_tokenizer *tokenizer)
{
	while (is_whitespace(tokenizer->cur))
		t_read_char(tokenizer);
}

static void	connect_node(t_token *token, t_token_node *node)
{
	if (token->size == 0)
		token->head = node;
	else
		token->tail->next = node;
	token->tail = node;
	token->size++;
}

t_token_node	*t_tokenize_word(t_tokenizer *tokenizer)
{
	const size_t	pos = tokenizer->pos;
	char			*literal;
	t_token_node	*node;

	while (!t_at_eof(tokenizer) && !is_metacharacter(tokenizer->cur))
		t_read_char(tokenizer);
	literal = ft_substr(tokenizer->input, pos, tokenizer->pos - pos);
	if (literal == NULL)
	{
		perror("ft_substr");
		exit(EXIT_FAILURE);
	}
	node = new_token_node(TK_WORD, literal);
	return (node);
}
