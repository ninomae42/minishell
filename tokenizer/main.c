#include "tokenizer.h"

int	main(int argc, char **argv)
{
	char	*input;
	bool	is_tokenize_error;
	t_token	*current;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	input = argv[1];
	is_tokenize_error = false;
	current = tokenize(input, &is_tokenize_error);
	if (is_tokenize_error)
		exit(EXIT_FAILURE);
	while (current->next != NULL)
	{
		printf("type: %d, literal: [%s]\n", current->type, current->literal);
		current = current->next;
	}
	exit(EXIT_SUCCESS);
}
