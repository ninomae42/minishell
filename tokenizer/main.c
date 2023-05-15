#include "tokenizer.h"

// create a new token. and connect to current token node
t_token	*new_token(t_token *current, t_token_type type, char *literal)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	current->next = new;
	new->type = type;
	new->literal = literal;
	new->next = NULL;
	return (new);
}

// copys token literal and create new token node
t_token	*duplicate_word(t_token *cur, t_token_type type, char *begin, char *end)
{
	char	*literal;

	literal = strndup(begin, end - begin);
	if (literal ==  NULL)
		return (NULL);
	cur = new_token(cur, type, literal);
	if (cur ==  NULL)
		return (NULL);
	return (cur);
}

t_token	*tokenize_metacharacter(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	end++;
	cur = duplicate_word(cur, find_token_type(*begin), (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize single quoted word sequence
t_token	*tokenize_single_quote(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	end++;
	cur = duplicate_word(cur, TK_SINGLE_QUOTE, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	begin = end;
	while (*end && *end != SINGLE_QUOTE)
		end++;
	if (*end == '\0')
		return (NULL);
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	begin = end;
	end++;
	cur = duplicate_word(cur, TK_SINGLE_QUOTE, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize double quoted word sequence
t_token	*tokenize_double_quote(t_token *cur, char **input)
{
	const char	*begin = *input;
	const char	*end = *input;

	end++;
	cur = duplicate_word(cur, TK_DOUBLE_QUOTE, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	begin = end;
	while (*end && *end != DOUBLE_QUOTE)
	{
		end++;
	}
	if (*end == '\0')
		return (NULL);
	cur = duplicate_word(cur, TK_WORD, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	begin = end;
	end++;
	cur = duplicate_word(cur, TK_DOUBLE_QUOTE, (char *)begin, (char *)end);
	if (cur ==  NULL)
		return (NULL);
	*input = (char *)end;
	return (cur);
}

// tokenize word
t_token	*tokenize_word(t_token *cur, char **input)
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
		else if (*input ==  SINGLE_QUOTE)
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

int	main(int argc, char **argv)
{
	char	*input;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	input = argv[1];
	bool	is_tokenize_error = false;
	t_token	*current = tokenize(input, &is_tokenize_error);
	if (is_tokenize_error)
		exit(EXIT_FAILURE);
	while (current->next != NULL)
	{
		printf("type: %d, literal: [%s]\n", current->type, current->literal);
		current = current->next;
	}
	exit(EXIT_SUCCESS);
}
