#ifndef PARSER_H
# define PARSER_H
# include "tokenizer.h"

typedef enum e_node_kind	t_node_kind;
enum e_node_kind
{
	ND_WORD,
	ND_SIMPLE_COMMAND,
};

typedef struct s_ast_node	t_ast_node;
struct s_ast_node
{
	t_node_kind	kind;
	t_ast_node	*child;
	t_ast_node	*brother;
	char		*literal;
};

typedef struct s_ast		t_ast;
struct s_ast
{
	t_ast_node	*root;
};

// ast.c
t_ast		*new_ast(void);
t_ast_node	*new_ast_node(t_node_kind kind,
				t_ast_node *child, t_ast_node *brother, char *word);
void		ast_destroy(t_ast *ast);
void		ast_print(t_ast *ast);

#endif
