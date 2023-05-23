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
	if (type == ND_PIPELINE)
		return "ND_PIPELINE";
	return "UNKNOWN";
}

t_node	*simple_command(t_parser *parser);
t_node	*simple_command_element(t_parser *parser);
t_node	*redirection(t_parser *parser);
t_node	*word(t_parser *parser);

t_node	*pipeline(t_parser *parser)
{
	t_node	*node;

	puts("pipeline");
	node = simple_command(parser);
	while (parser->token->type != TK_EOF)
	// while (1)
	{
		printf("[PIPE]CURRENT type: %d, literal: %s\n", parser->token->type, parser->token->literal);
		if (parser->token->type != TK_EOF)
		{
			parser->token = parser->token->next;
			node = new_node(ND_PIPELINE, node, simple_command(parser));
		}
		else
			return (node);
	}
	// return (node);
	return (new_node(ND_SIMPLE_COMMAND, node, NULL));
}

t_node	*simple_command(t_parser *parser)
{
	t_node	*node;

	puts("simple_command");
	node = simple_command_element(parser);
		printf("CURRENT type: %d, literal: %s\n", parser->token->type, parser->token->literal);
	while (parser->token->type != TK_EOF)
	// while (1)
	{
		printf("CURRENT type: %d, literal: %s\n", parser->token->type, parser->token->literal);
		if (parser->token->type == TK_EOF
			|| (parser->token->type == TK_OP && strcmp(parser->token->literal, "|") == 0)
		)
			return (node);
		else
			node = new_node(ND_SIMPLE_COMMAND_ELEMENT, node, simple_command_element(parser));
			// node = new_node(ND_SIMPLE_COMMAND, node, simple_command_element(parser));
		// if (parser->token->type == TK_EOF)
		// 	node = new_node(ND_SIMPLE_COMMAND, node, simple_command_element(parser));
		// else
		// 	return (node);
	}
	// return (new_node(ND_SIMPLE_COMMAND, node, NULL));
	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, node, NULL));
}

t_node	*simple_command_element(t_parser *parser)
{
	t_node	*node;

	puts("simple_command_element");
	// if (parser->token->type == TK_WORD)
	// 	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, word(parser), NULL));
	// if (strcmp(parser->token->literal, "<") == 0)
	// 	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, redirection(parser), NULL));
	// if (strcmp(parser->token->literal, "<<") == 0)
	// 	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, redirection(parser), NULL));
	// if (strcmp(parser->token->literal, ">") == 0)
	// 	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, redirection(parser), NULL));
	// if (strcmp(parser->token->literal, ">>") == 0)
	// 	return (new_node(ND_SIMPLE_COMMAND_ELEMENT, redirection(parser), NULL));

	if (parser->token->type == TK_WORD)
		return (word(parser));
	if (strcmp(parser->token->literal, "<") == 0)
		return (redirection(parser));
	if (strcmp(parser->token->literal, "<<") == 0)
		return (redirection(parser));
	if (strcmp(parser->token->literal, ">") == 0)
		return (redirection(parser));
	if (strcmp(parser->token->literal, ">>") == 0)
		return (redirection(parser));
	return (NULL);
}

t_node	*redirection(t_parser *parser)
{
	t_node	*node;
	t_token	*token;

	puts("redirection");
	token = parser->token;
	parser->token = parser->token->next;
	if (strcmp(token->literal, "<") == 0)
		return (new_node(ND_REDIRECT_IN, word(parser), NULL));
	if (strcmp(token->literal, "<<") == 0)
		return (new_node(ND_REDIRECT_IN_HDOC, word(parser), NULL));
	if (strcmp(token->literal, ">") == 0)
		return (new_node(ND_REDIRECT_OUT, word(parser), NULL));
	if (strcmp(token->literal, ">>") == 0)
		return (new_node(ND_REDIRECT_OUT_APPEND, word(parser), NULL));
	return (NULL);
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
	// printf("type: %s, word: %s\n", node_type2str(ast->type), ast->word);
	print_ast(ast->lhs);
	printf("type: %s, word: %s\n", node_type2str(ast->type), ast->word);
	print_ast(ast->rhs);
}

int	main(void)
{
	t_token	**tokens;

	tokens = (t_token **)malloc(sizeof(t_token *) * 9);
	if (!tokens)
		return (1);
	tokens[0] = malloc(sizeof(t_token));
	tokens[1] = malloc(sizeof(t_token));
	tokens[2] = malloc(sizeof(t_token));
	tokens[3] = malloc(sizeof(t_token));
	tokens[4] = malloc(sizeof(t_token));
	tokens[5] = malloc(sizeof(t_token));
	tokens[6] = malloc(sizeof(t_token));
	tokens[7] = malloc(sizeof(t_token));
	tokens[8] = malloc(sizeof(t_token));

	tokens[0]->literal = strdup("<");
	tokens[0]->type = TK_OP;
	tokens[0]->next = tokens[1];

	tokens[1]->literal = strdup("input.txt");
	tokens[1]->type = TK_WORD;
	tokens[1]->next = tokens[2];

	tokens[2]->literal = strdup("cat");
	tokens[2]->type = TK_WORD;
	tokens[2]->next = tokens[3];

	tokens[3]->literal = strdup("|");
	tokens[3]->type = TK_OP;
	tokens[3]->next = tokens[4];

	tokens[4]->literal = strdup("grep");
	tokens[4]->type = TK_WORD;
	tokens[4]->next = tokens[5];

	tokens[5]->literal = strdup("ft");
	tokens[5]->type = TK_WORD;
	tokens[5]->next = tokens[6];

	tokens[6]->literal = strdup(">>");
	tokens[6]->type = TK_OP;
	tokens[6]->next = tokens[7];

	tokens[7]->literal = strdup("output.txt");
	tokens[7]->type = TK_WORD;
	tokens[7]->next = tokens[8];

	tokens[8]->literal = NULL;
	tokens[8]->type = TK_EOF;
	tokens[8]->next = NULL;

	t_parser	parser;
	parser.token = tokens[0];

	// t_node	*ast = simple_command(&parser);
	t_node	*ast = pipeline(&parser);
	print_ast(ast);
}

// t_node	*simple_command_element(t_parser *parser)
// {
// t_node	*node;
//
// node = word(parser);
// while (1)
// {
// 	if (parser->token->type == TK_WORD)
// 		node = new_node(ND_SIMPLE_COMMAND_ELEMENT, node, word(parser));
// 	else
// 		return (node);
// }
// }
