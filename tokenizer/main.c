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

t_token	*token_metacharacter(t_token *current, char **begin, char **end)
{
	char	*begin_loc;
	char	*end_loc;

	begin_loc = *begin;
	end_loc = *end;
	end_loc++;
	current = new_token(current, find_token_type(*begin_loc), strndup(begin_loc, end_loc - begin_loc));
	begin_loc = end_loc;
	*begin = begin_loc;
	*end = end_loc;
	return (current);
}

// tokenize input and return token nodes.
t_token	*tokenize(char *input)
{
	t_token	head;
	t_token	*current;
	char	*end;

	head.next = NULL;
	current = &head;
	end = input;
	while (*input != '\0')
	{
		if (is_meta_character(*input))
		{
			current = token_metacharacter(current, &input, &end);
			continue ;
		}
		while (*end != '\0' && !is_meta_character(*input))
			end++;
		current = new_token(current, TK_WORD, strndup(input, end - input));
		input = end;
	}
	current = new_token(current, TK_EOF, NULL);
	return (head.next);
}

int	main(int argc, char **argv)
{
	char	*input;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	input = argv[1];
	t_token	*current = tokenize(input);
	while (current->next != NULL)
	{
		printf("type: %d, literal: [%s]\n", current->type, current->literal);
		current = current->next;
	}
	exit(EXIT_SUCCESS);
}
