#include "tokenizer.h"

bool	is_argc_valid(int argc)
{
	return (argc == 2);
}

void	skip_blanks(char **begin)
{
	const char	*current = *begin;

	while (*current && is_blank(*current))
		current++;
	*begin = (char *)current;
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
		else
			cur = tokenize_word(cur, &input, is_err);
	}
	cur = new_token(cur, TK_EOF, NULL);
	return (head.next);
}

int	main(int argc, char **argv)
{
	t_token	*token;
	t_token	*current;
	bool	is_error;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	is_error = false;
	token = tokenize(argv[1], &is_error);
	current = token;
	while (current != NULL)
	{
		printf("type: %d, literal: %s\n", current->type, current->literal);
		current = current->next;
	}
	exit(EXIT_SUCCESS);
}
