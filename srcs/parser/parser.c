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

size_t	count_words(t_node *current)
{
	size_t	cnt;

	cnt = 0;
	while (current != NULL)
	{
		if (current->child != NULL && current->child->type == ND_WORD)
			cnt++;
		current = current->brother;
	}
	return (cnt);
}

t_node	*new_node(t_node_type type, t_node *child)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		perror_exit("malloc");
	memset(node, 0, sizeof(t_node));
	node->type = type;
	node->child = child;
	return (node);
}

t_node	*word(t_parser *parser)
{
	t_node	*node;

	if (parser->token == NULL || parser->token->type == TK_EOF)
		return (NULL);
	node = new_node(ND_WORD, NULL);
	node->word = strdup(parser->token->literal);
	parser->token = parser->token->next;
	return (node);
}

t_node	*simple_command_element(t_parser *parser)
{
	t_node	*head;
	t_node	*current;

	head = new_node(ND_SIMPLE_COMMAND_ELEMENT, word(parser));
	current = head;
	while (true)
	{
		if (parser->token == NULL || parser->token->type == TK_EOF)
			return (head);
		if (parser->token->type == TK_WORD)
			current->brother = new_node(ND_SIMPLE_COMMAND_ELEMENT, word(parser));
		current = current->brother;
	}
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;

	node = new_node(ND_SIMPLE_COMMAND, NULL);
	node->child = simple_command_element(parser);
	printf("words count: %zu\n", count_words(node->child));
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
