#ifndef EXPANDER_H
# define EXPANDER_H
# include "parser.h"
# include "minishell.h"

char	*concat_str(char *s1, char *s2);
char	*expand_word(char *word);
void	expand(t_ast *ast);

// expander_utils.c
char	*get_escaped_str(char *s);
#endif
