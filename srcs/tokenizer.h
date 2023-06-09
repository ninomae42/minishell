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

typedef struct s_tokenizer	t_tokenizer;
struct s_tokenizer
{
	char	*input;
	size_t	input_len;
	size_t	pos;
	size_t	read_pos;
	char	cur;
};

/* pos -> current position in input (points to current char)
 * read_pos -> current reading position in input (after current char)
 * cur-> current char under examination
 * */

// tokenizer.c
t_tokenizer		*new_tokenizer(char *input);
void			tokenizer_destroy(t_tokenizer *tokenizer);
void			t_read_char(t_tokenizer *tokenizer);
char			t_peek_char(t_tokenizer *tokenizer);
bool			t_at_eof(t_tokenizer *tokenizer);

// tokenizer_main.c
t_token			*tokenize(char *input);
t_token_node	*t_tokenize_word(t_tokenizer *tokenizer);

// token.c
t_token			*new_token(void);
t_token_node	*new_token_node(t_token_kind kind, char *literal);
void			token_destroy(t_token *token);
void			token_print(t_token *token);

// tokenizer_ctype.c
bool			is_metacharacter(char c);
bool			is_whitespace(char c);

#endif
