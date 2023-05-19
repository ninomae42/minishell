#include "tokenizer.h"

void	perror_exit(char *func_name)
{
	perror(func_name);
	exit(EXIT_FAILURE);
}
