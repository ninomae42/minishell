#include "tokenizer.h"

bool	is_argc_valid(int argc)
{
	return (argc == 2);
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
