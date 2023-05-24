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
	t_node		*child;
	t_node		*brother;
	char		*word;
};

typedef struct s_parser
{
	t_token	*token;
}	t_parser;

t_node	*parse(t_token *token);
void	print_ast_pre_order(t_node *ast);
void	dealloc_ast(t_node *ast);

size_t	count_words(t_node *current);

#endif
