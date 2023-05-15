#include "tokenizer.h"

static t_token	*tokenize_metacharacter(t_token *cur, char **input);
static t_token	*tokenize_single_quote(t_token *cur, char **input);
static t_token	*tokenize_double_quote(t_token *cur, char **input);
static t_token	*tokenize_word(t_token *cur, char **input);

// tokenize input and return token nodes.
t_token	*tokenize(char *input, bool *is_error)
{
	t_token	head;
	t_token	*current;

	head.next = NULL;
	current = &head;
	while (*input && current)
	{
		if (is_meta_character(*input))
			current = tokenize_metacharacter(current, &input);
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
static t_token	*tokenize_metacharacter(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	end++;
	cur = duplicate_word(cur,
			find_token_type(*begin), (char *)begin, (char *)end);
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

	end++;
	cur = duplicate_word(cur, TK_SINGLE_QUOTE, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	begin = end;
	while (*end && *end != SINGLE_QUOTE)
		end++;
	if (*end == '\0')
		return (NULL);
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	begin = end;
	end++;
	cur = duplicate_word(cur, TK_SINGLE_QUOTE, (char *)begin, (char *)end);
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

	end++;
	cur = duplicate_word(cur, TK_DOUBLE_QUOTE, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	begin = end;
	while (*end && *end != DOUBLE_QUOTE)
	{
		end++;
	}
	if (*end == '\0')
		return (NULL);
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur == NULL)
		return (NULL);
	begin = end;
	end++;
	cur = duplicate_word(cur, TK_DOUBLE_QUOTE, (char *)begin, (char *)end);
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
