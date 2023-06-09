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

typedef struct s_parser		t_parser;
struct s_parser
{
	t_token			*token;
	t_token_node	*cur_tok;
	t_token_node	*peek_tok;
};

// parser.c
t_parser	*new_parser(t_token *token);
void		p_next_token(t_parser *parser);
void		parser_destroy(t_parser *parser);

// parser_utils.c
bool		p_at_eof(t_parser *parser);
bool		p_cur_is(t_parser *parser, t_token_kind kind);
bool		p_peek_is(t_parser *parser, t_token_kind kind);

// ast.c
t_ast		*new_ast(void);
t_ast_node	*new_ast_node(t_node_kind kind,
				t_ast_node *child, t_ast_node *brother, char *word);
void		ast_destroy(t_ast *ast);
void		ast_print(t_ast *ast);

#endif
