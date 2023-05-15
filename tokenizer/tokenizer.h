#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define META_CHARACTERS " \t\n|&;()<>"
# define BRANK_CHARACTERS " \t"
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

typedef enum e_token_type
{
	TK_EOF,
	TK_SPACE,
	TK_TAB,
	TK_NEWLINE,
	TK_PIPE,
	TK_AMP,
	TK_SEMICOLON,
	TK_LPAREN,
	TK_RPAREN,
	TK_LT,
	TK_GT,
	TK_SINGLE_QUOTE,
	TK_DOUBLE_QUOTE,
	TK_WORD,
}	t_token_type;

typedef struct s_token{
	t_token_type	type;
	char			*literal;
	struct s_token	*next;
}	t_token;

bool			is_argc_valid(int argc);
bool			is_meta_character(char c);
t_token_type	find_token_type(char c);

t_token			*tokenize(char *input, bool *is_error);
t_token			*duplicate_word(
					t_token *cur, t_token_type type, char *begin, char *end);
t_token			*new_token(t_token *current, t_token_type type, char *literal);

#endif
