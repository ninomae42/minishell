/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:05:50 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:05:51 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "tokenizer.h"

typedef enum e_node_kind	t_node_kind;
enum e_node_kind
{
	ND_WORD,
	ND_REDIRECT_IN,
	ND_REDIRECT_IN_HDOC,
	ND_REDIRECT_OUT,
	ND_REDIRECT_OUT_APPEND,
	ND_SIMPLE_COMMAND,
	ND_PIPELINE,
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
	bool			is_syntax_err;
};

// parser_main.c
t_ast		*parse(t_token *token);

// parser_simple_command.c
t_ast_node	*parse_simple_command(t_parser *parser);
t_ast_node	*parse_word(t_parser *parser);
bool		p_is_simple_command_element(t_parser *p);

// parser_redirect.c
t_ast_node	*parse_redirect(t_parser *p);

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
void		ast_node_destroy(t_ast_node *node);

// ast_utils.c
char		*node_kind_to_str(t_node_kind kind);
void		ast_print(t_ast *ast);

#endif
