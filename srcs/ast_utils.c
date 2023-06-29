#include "parser.h"

char	*node_kind_to_str(t_node_kind kind)
{
	if (kind == ND_WORD)
		return ("ND_WORD");
	if (kind == ND_REDIRECT_IN)
		return ("ND_REDIRECT_IN");
	if (kind == ND_REDIRECT_IN_HDOC)
		return ("ND_REDIRECT_IN_HDOC");
	if (kind == ND_REDIRECT_OUT)
		return ("ND_REDIRECT_OUT");
	if (kind == ND_REDIRECT_OUT_APPEND)
		return ("ND_REDIRECT_OUT_APPEND");
	if (kind == ND_SIMPLE_COMMAND)
		return ("ND_SIMPLE_COMMAND");
	if (kind == ND_PIPELINE)
		return ("ND_PIPELINE");
	return ("UNKNOWN");
}

static void	ast_print_internal(t_ast_node *node)
{
	t_ast_node	*child;
	t_ast_node	*brother;

	if (node == NULL)
		return ;
	child = node->child;
	brother = node->brother;
	printf("nd_kind: %s, literal: %s\n",
		node_kind_to_str(node->kind), node->literal);
	ast_print_internal(child);
	ast_print_internal(brother);
}

void	ast_print(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ast_print_internal(ast->root);
}
