#ifndef TOKENIZER_H
# define TOKENIZER_H
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define META_CHARACTERS " \t\n|&;()<>"
# define OPERATOR_CHARACTERS "\n|&;()<>"
# define BRANK_CHARACTERS " \t"
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '"'

typedef enum e_token_type
{
	TK_EOF,
	TK_WORD,
	TK_OPERATOR,
}	t_token_type;

typedef struct s_token{
	t_token_type	type;
	char			*literal;
	struct s_token	*next;
}	t_token;

bool	is_blank(char c);
bool	is_meta_character(char c);
bool	is_operator_charcter(char c);

t_token	*new_token(t_token *cur, t_token_type type, char *literal);
void	skip_blanks(char **begin);

#endif
