#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e_token_type {
	TK_WORD,
	TK_OP,
	TK_EOF,
}	t_token_type;

typedef struct s_token	t_token;
struct s_token{
	t_token_type	type;
	char			*literal;
	t_token			*next;
};

typedef struct s_node	t_node;

typedef enum e_node_type t_node_type;
enum e_node_type{
	ND_SIMPLE_COMMAND_ELEMENT,
	ND_SIMPLE_COMMAND,
	ND_WORD,
	ND_REDIRECT,
	ND_PIPELINE,
	ND_LIST,
	ND_COMPOUND,
	ND_REDIRECT_IN,
	ND_REDIRECT_IN_HDOC,
	ND_REDIRECT_OUT,
	ND_REDIRECT_OUT_APPEND,
};

struct s_node{
	t_node_type	type;
	t_node		*lhs;
	t_node		*rhs;
	char		*word;
};

typedef struct s_parser
{
	t_token	*token;
}	t_parser;

t_node	*new_node(t_node_type type, t_node *lhs, t_node *rhs)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = type;
	node->lhs = lhs;
	node->rhs = rhs;
	node->word = NULL;
	return (node);
}

char	*node_type2str(t_node_type type)
{
	if (type == ND_SIMPLE_COMMAND_ELEMENT)
		return "ND_SIMPLE_COMMAND_ELEMENT";
	if (type == ND_SIMPLE_COMMAND)
		return "ND_SIMPLE_COMMAND";
	if (type == ND_WORD)
		return "ND_WORD";
	if (type == ND_REDIRECT)
		return "ND_REDIRECT";
	if (type == ND_REDIRECT_IN)
		return "ND_REDIRECT_IN";
	if (type == ND_REDIRECT_IN_HDOC)
		return "ND_REDIRECT_IN_HDOC";
	if (type == ND_REDIRECT_OUT)
		return "ND_REDIRECT_OUT";
	if (type == ND_REDIRECT_OUT_APPEND)
		return "ND_REDIRECT_OUT_APPEND";
	return "UNKNOWN";
}

t_node	*simple_command(t_parser*token);
t_node	*pipeline(t_parser *token);
t_node	*list(t_parser *token);
t_node	*compound(t_parser *token);
t_node	*word(t_parser *token);
t_node	*redirect(t_parser *token);

t_node	*command(t_parser *parser)
{
	t_node	*node;

	node = simple_command(parser);
	// while (1)
	// {
	// 	if (token->current->type != TK_EOF)
	// 		node = new_node(ND_SIMPLE_COMMAND, simple_command(token), NULL);
	// 	else
	// 		return (node);
	// }
	return (node);
}

t_node	*simple_command_element(t_parser *parser);

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;

	puts("first simplecommand");
	node = simple_command_element(parser);
	while (1)
	{
		if (parser->token->type != TK_EOF)
		{
			puts("second simplecommand");
			node = new_node(ND_SIMPLE_COMMAND, node, simple_command_element(parser));
		}
			// node = new_node(ND_SIMPLE_COMMAND, simple_command_element(parser), node);
		else
			return (node);
	}
}
t_node	*simple_command_element(t_parser *parser)
{
	t_node	*node;

	if (parser->token->type == TK_WORD)
		node = new_node(ND_SIMPLE_COMMAND_ELEMENT, word(parser), NULL);
	else
		node = new_node(ND_SIMPLE_COMMAND_ELEMENT, redirect(parser), NULL);
	return (node);
}

t_node	*redirect(t_parser *parser)
{
	t_node	*node;
	t_token	*tmp;

	puts("redirect");
	tmp = parser->token;
	parser->token = parser->token->next;
	if (strcmp(tmp->literal, "<") == 0)
		node = new_node(ND_REDIRECT_IN, word(parser), NULL);
	if (strcmp(tmp->literal, "<<") == 0)
		node = new_node(ND_REDIRECT_IN_HDOC, word(parser), NULL);
	if (strcmp(tmp->literal, ">") == 0)
		node = new_node(ND_REDIRECT_OUT, word(parser), NULL);
	if (strcmp(tmp->literal, ">>") == 0)
		node = new_node(ND_REDIRECT_OUT_APPEND, word(parser), NULL);
	return (node);
}


t_node	*word(t_parser *parser)
{
	t_node	*node;

	puts("word");
	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = ND_WORD;
	node->lhs = NULL;
	node->rhs = NULL;
	node->word = strdup(parser->token->literal);
	parser->token = parser->token->next;
	return (node);
}

void	print_ast(t_node *ast)
{
	if (ast == NULL)
		return ;
	printf("type: %s, word: %s\n", node_type2str(ast->type), ast->word);
	print_ast(ast->lhs);
	print_ast(ast->rhs);
}

int	main(void)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *) * 6);
	if (!tokens)
		return (1);
	tokens[0] = malloc(sizeof(t_token));
	tokens[1] = malloc(sizeof(t_token));
	tokens[2] = malloc(sizeof(t_token));
	tokens[3] = malloc(sizeof(t_token));
	tokens[4] = malloc(sizeof(t_token));
	tokens[5] = malloc(sizeof(t_token));
	tokens[0]->literal = strdup("<");
	tokens[0]->type = TK_OP;
	tokens[0]->next = tokens[1];

	tokens[1]->literal = strdup("input.txt");
	tokens[1]->type = TK_WORD;
	tokens[1]->next = tokens[2];

	tokens[2]->literal = strdup("cat");
	tokens[2]->type = TK_WORD;
	tokens[2]->next = tokens[3];

	tokens[3]->literal = strdup(">>");
	tokens[3]->type = TK_OP;
	tokens[3]->next = tokens[4];

	tokens[4]->literal = strdup("output.txt");
	tokens[4]->type = TK_WORD;
	tokens[4]->next = tokens[5];

	tokens[5]->literal = NULL;
	tokens[5]->type = TK_EOF;
	tokens[5]->next = NULL;

	t_parser	parser;
	parser.token = tokens[0];

	t_node	*ast = command(&parser);
	puts("ikigake");
	print_ast(ast);
}
