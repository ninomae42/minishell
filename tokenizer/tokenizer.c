#include "tokenizer.h"

static t_token	*tokenize_operators(t_token *cur, char **input);
static t_token	*tokenize_single_quote(t_token *cur, char **input);
static t_token	*tokenize_double_quote(t_token *cur, char **input);
static t_token	*tokenize_word(t_token *cur, char **input);

bool	is_blank(char c)
{
	return (c ==  ' ' || c ==  '\t');
}

void	skip_spaces(char **input)
{
	const char *end = *input;

	while (*end != '\0' && is_blank(*end))
		end++;
	*input = (char *)end;
}

// tokenize input and return token nodes.
t_token	*tokenize(char *input, bool *is_error)
{
	t_token	head;
	t_token	*current;

	head.next = NULL;
	current = &head;
	while (*input && current)
	{
		if (is_blank(*input))
			skip_spaces(&input);
		else if (is_operator_chars(*input))
			current = tokenize_operators(current, &input);
		else if (*input == SINGLE_QUOTE)
			current = tokenize_single_quote(current, &input);
		else if (*input == DOUBLE_QUOTE)
			current = tokenize_double_quote(current, &input);
		else
			current = tokenize_word(current, &input);
	}
	if (current == NULL)
		*is_error = true;
	else
		current = new_token(current, TK_EOF, NULL);
	return (head.next);
}

// tokenize metacharacter
static t_token	*tokenize_operators(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	while (*end && is_operator_chars(*end))
		end++;
	cur = duplicate_word(cur, TK_OPERATOR, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize single quoted word sequence
static t_token	*tokenize_single_quote(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	while (*end && !is_meta_character(*end))
		end++;
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize double quoted word sequence
static t_token	*tokenize_double_quote(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	while (*end && !is_meta_character(*end))
		end++;
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize word
static t_token	*tokenize_word(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	while (*end && !is_meta_character(*end))
	{
		if (*end == SINGLE_QUOTE)
			return (NULL);
		end++;
	}
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}
