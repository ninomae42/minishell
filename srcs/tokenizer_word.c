#include "tokenizer.h"

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
