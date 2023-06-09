#include "exec.h"

size_t	count_argc(t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			i++;
		node = node->brother;
	}
	return (i);
}

char	**dup_argv(t_ast_node *node, size_t argc)
{
	char	**argv;
	size_t	i;

	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			argv[i++] = node->literal;
		node = node->brother;
	}
	argv[i] = NULL;
	return (argv);
}
