#include "tokenizer.h"

int	main(int argc, char **argv)
{
	char	*input;

	if (!is_argc_valid(argc))
		exit(EXIT_FAILURE);
	input = argv[1];
	printf("input: %s\n", input);
	exit(EXIT_SUCCESS);
}
