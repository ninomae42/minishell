#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define META_CHARACTERS " \t\n|&;()<>"
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

}	t_token_type;

typedef struct s_token{
	t_token_type	type;
	char			*literal;
	struct s_token	*next;
}	t_token;

bool			is_argc_valid(int argc);
bool			is_meta_character(char c);
t_token_type	find_token_type(char c);

#endif
