#include "tokenizer.h"

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
