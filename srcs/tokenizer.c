#include "tokenizer.h"

void	t_read_char(t_tokenizer *tokenizer);

t_tokenizer	*new_tokenizer(char *input)
{
	t_tokenizer	*t;

	t = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (t == NULL)
		err_fatal(errno);
	t->input = input;
	t->input_len = ft_strlen(input);
	t->pos = 0;
	t->read_pos = 0;
	t->is_in_quote = false;
	t->is_error = false;
	t_read_char(t);
	return (t);
}

void	t_read_char(t_tokenizer *tokenizer)
{
	if (tokenizer->input_len <= tokenizer->read_pos)
		tokenizer->cur = 0;
	else
		tokenizer->cur = tokenizer->input[tokenizer->read_pos];
	tokenizer->pos = tokenizer->read_pos;
	tokenizer->read_pos++;
}

char	t_peek_char(t_tokenizer *tokenizer)
{
	if (tokenizer->input_len <= tokenizer->read_pos)
		return ('\0');
	return (tokenizer->input[tokenizer->read_pos]);
}

bool	t_at_eof(t_tokenizer *tokenizer)
{
	return (tokenizer->cur == '\0');
}

void	tokenizer_destroy(t_tokenizer *tokenizer)
{
	free(tokenizer);
}
