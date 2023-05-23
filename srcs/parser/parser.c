#include "parser.h"

char	*node_type2str(t_node_type type)
{
	if (type == ND_WORD)
		return ("ND_WORD");
	if (type == ND_SIMPLE_COMMAND_ELEMENT)
		return ("ND_SIMPLE_COMMAND_ELEMENT");
	if (type == ND_SIMPLE_COMMAND)
		return ("ND_SIMPLE_COMMAND");
	return ("Unknown");
}

void	print_ast_pre_order(t_node *ast)
{
	t_node	*child;
	t_node	*sibling;

	if (ast == NULL)
		return ;
	child = ast->child;
	sibling = ast->brother;

	printf("type: %s, word: %s\n", node_type2str(ast->type), ast->word);
	print_ast_pre_order(child);
	print_ast_pre_order(sibling);
}

t_node	*new_node(t_node_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		perror_exit("malloc");
	memset(node, 0, sizeof(t_node));
	node->type = type;
	return (node);
}

t_node	*word(t_parser *parser)
{
	t_node	*node;

	if (parser->token == NULL || parser->token->type == TK_EOF)
		return (NULL);
	node = new_node(ND_WORD);
	node->word = strdup(parser->token->literal);
	parser->token = parser->token->next;
	return (node);
}

t_node	*simple_command_element(t_parser *parser)
{
	t_node	*head;
	t_node	*current;

	head = word(parser);
	current = head;
	while (true)
	{
		if (parser->token == NULL || parser->token->type == TK_EOF)
			return (head);
		if (parser->token->type == TK_WORD)
			current->brother = word(parser);
		current = current->brother;
	}
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_COMMAND);
	node->child = new_node(ND_SIMPLE_COMMAND_ELEMENT);
	node->child->brother = simple_command_element(parser);
	return (node);
}

t_node	*parse(t_token *token)
{
	t_parser	parser;
	t_node		*ast;

	parser.token = token;
	ast = simple_command(&parser);
	return (ast);
}
