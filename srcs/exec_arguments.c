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

char	**alloc_argv(size_t argc)
{
	char	**argv;

	argv = (char **)malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
		ft_fatal("malloc");
	return (argv);
}

void	set_argv(char **argv, t_ast_node *node)
{
	size_t	i;

	i = 0;
	while (node != NULL)
	{
		if (node->kind == ND_WORD)
			argv[i] = node->literal;
		i++;
		node = node->brother;
	}
	argv[i] = NULL;
}

