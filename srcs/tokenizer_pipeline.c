#include "tokenizer.h"

bool	t_is_pipeline(t_tokenizer *tokenizer)
{
	return (is_pipeline_character(tokenizer->cur));
}

t_token_node	*t_tokenize_pipeline(t_tokenizer *tokenizer)
{
	t_token_node	*node;

	node = new_token_node(TK_PIPELINE, ft_strdup("|"));
	t_read_char(tokenizer);
	return (node);
}
