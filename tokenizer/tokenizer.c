#include "tokenizer.h"

static t_token	*tokenize_operator(t_token *cur, char **cur_ch);
static t_token	*tokenize_quotes(t_token *cur, char **cur_ch, char quote_ch);
static t_token	*tokenize_word(t_token *cur, char **cur_ch, bool *is_err);

t_token	*tokenize(char *input, bool *is_err)
{
	t_token	head;
	t_token	*cur;

	head.next = NULL;
	cur = &head;
	while (*input && !*is_err)
	{
		if (is_blank(*input))
			skip_blanks(&input);
		else if (is_operator_charcter(*input))
			cur = tokenize_operator(cur, &input);
		else if (*input == SINGLE_QUOTE)
			cur = tokenize_quotes(cur, &input, SINGLE_QUOTE);
		else if (*input == DOUBLE_QUOTE)
			cur = tokenize_quotes(cur, &input, DOUBLE_QUOTE);
		else
			cur = tokenize_word(cur, &input, is_err);
	}
	cur = new_token(cur, TK_EOF, NULL);
	return (head.next);
}

t_token	*tokenize_operator(t_token *cur, char **cur_ch)
{
	const char	*begin = *cur_ch;
	const char	*end = *cur_ch;
	char		*literal;

	while (*end && is_operator_charcter(*end))
		end++;
	literal = strndup(begin, end - begin);
	if (literal == NULL)
		perror_exit("strndup");
	cur = new_token(cur, TK_OPERATOR, literal);
	if (cur == NULL)
		perror_exit("malloc");
	*cur_ch = (char *)end;
	return (cur);
}

t_token	*tokenize_quotes(t_token *cur, char **cur_ch, char quote_ch)
{
	const char	*begin = *cur_ch;
	const char	*end = *cur_ch;
	char		*literal;

	end++;
	while (*end && *end != quote_ch)
		end++;
	if (*end && *end == quote_ch)
		end++;
	literal = strndup(begin, end - begin);
	if (literal == NULL)
		perror_exit("strndup");
	cur = new_token(cur, TK_WORD, literal);
	if (cur == NULL)
		perror_exit("malloc");
	*cur_ch = (char *)end;
	return (cur);
}

t_token	*tokenize_word(t_token *cur, char **cur_ch, bool *is_err)
{
	const char	*begin = *cur_ch;
	const char	*end = *cur_ch;
	char		*literal;

	while (*end && !is_meta_character(*end))
		end++;
	literal = strndup(begin, end - begin);
	if (literal == NULL)
	{
		*is_err = true;
		return (NULL);
	}
	cur = new_token(cur, TK_WORD, literal);
	*cur_ch = (char *)end;
	return (cur);
}
