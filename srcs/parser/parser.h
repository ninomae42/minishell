#ifndef PARSER_H
# define PARSER_H
# include "tokenizer.h"

typedef enum e_node_type	t_node_type;
enum e_node_type{
	ND_SIMPLE_COMMAND,
	ND_SIMPLE_COMMAND_ELEMENT,
	ND_WORD,
};

typedef struct s_node	t_node;
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

t_node	*parse(t_token *token);
void	print_ast_in_order(t_node *ast);

#endif
