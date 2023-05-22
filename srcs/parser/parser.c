#include "parser.h"

char	*node_type2str(t_node_type type)
{
	if (type == ND_SIMPLE_COMMAND)
		return "ND_SIMPLE_COMMAND";
	if (type == ND_SIMPLE_COMMAND_ELEMENT)
		return "ND_SIMPLE_COMMAND_ELEMENT";
	if (type == ND_WORD)
		return "ND_WORD";
	return "UNKNOWN";
}

void	print_ast_in_order(t_node *ast)
{
	if (ast == NULL)
		return ;
	print_ast_in_order(ast->lhs);
	printf("type: %s, word: %s\n", node_type2str(ast->type), ast->word);
	print_ast_in_order(ast->rhs);
}

t_node	*new_node(t_node_type type, t_node *lhs, t_node *rhs)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		perror_exit("malloc");
	node->type = type;
	node->lhs = lhs;
	node->rhs = rhs;
	node->word = NULL;
	return (node);
}

t_node	*word(t_parser *parser)
{
	t_node	*node;

	node = new_node(ND_WORD, NULL, NULL);
	node->word = strdup(parser->token->literal);
	parser->token = parser->token->next;
	return (node);
}

t_node	*simple_command_element(t_parser *parser, t_node *prev)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_COMMAND_ELEMENT, NULL, NULL);
	node->lhs = prev;
	if (parser->token->type == TK_WORD)
		node->rhs = word(parser);
	return (node);
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;

	node = simple_command_element(parser, NULL);
	while (true)
	{
		if (parser->token->type == TK_EOF)
			return (new_node(ND_SIMPLE_COMMAND, node, NULL));
		else
			node = simple_command_element(parser, node);
	}
}

t_node	*parse(t_token *token)
{
	t_parser	parser;
	t_node		*ast;

	parser.token = token;
	ast = simple_command(&parser);
	return (ast);
}
