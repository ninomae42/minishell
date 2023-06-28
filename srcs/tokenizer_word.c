#include "tokenizer.h"

static bool	is_single_quote(char c);
static bool	is_double_quote(char c);
static void	t_read_until_next_quote_char(t_tokenizer *tokenizer, char quote_c);

t_token_node	*t_tokenize_word(t_tokenizer *tokenizer)
{
	const size_t	pos = tokenizer->pos;
	char			*literal;
	t_token_node	*node;

	while (!t_at_eof(tokenizer) && !is_metacharacter(tokenizer->cur))
	{
		if (is_single_quote(tokenizer->cur) || is_double_quote(tokenizer->cur))
			t_read_until_next_quote_char(tokenizer, tokenizer->cur);
		else
			t_read_char(tokenizer);
	}
	if (t_at_eof(tokenizer) && tokenizer->is_in_quote)
	{
		tokenizer->is_error = true;
		err_put_tokenizer_unclosed_quote_err();
		return (NULL);
	}
	literal = ft_substr(tokenizer->input, pos, tokenizer->pos - pos);
	if (literal == NULL)
		ft_fatal("malloc");
	node = new_token_node(TK_WORD, literal);
	return (node);
}

static void	t_read_until_next_quote_char(t_tokenizer *tokenizer, char quote_c)
{
	tokenizer->is_in_quote = true;
	while (!t_at_eof(tokenizer))
	{
		t_read_char(tokenizer);
		if (tokenizer->cur == quote_c)
		{
			t_read_char(tokenizer);
			tokenizer->is_in_quote = false;
			break ;
		}
	}
}

static bool	is_single_quote(char c)
{
	return (c == '\'');
}

static bool	is_double_quote(char c)
{
	return (c == '"');
}
