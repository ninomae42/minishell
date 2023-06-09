#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "minishell.h"

typedef enum e_token_kind	t_token_kind;
enum e_token_kind
{
	TK_EOF,
	TK_WORD,
};

typedef struct s_token_node	t_token_node;
struct s_token_node
{
	t_token_kind	kind;
	char			*literal;
	t_token_node	*next;
};

typedef struct s_token	t_token;
struct s_token
{
	t_token_node	*head;
	t_token_node	*tail;
	size_t			size;
};

// token.c
t_token			*new_token(void);
t_token_node	*new_token_node(t_token_kind kind, char *literal);
void			token_destroy(t_token *token);
void			token_print(t_token *token);

#endif
