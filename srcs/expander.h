#ifndef EXPANDER_H
# define EXPANDER_H
# include "parser.h"
# include "minishell.h"

char	*concat_str(char *s1, char *s2);
char	*expand_word(char *word);
void	expand(t_ast *ast);

// expander_utils.c
bool	is_alpha_under(char c);
bool	is_alpha_num_under(char c);
char	*get_escaped_str(char *s);

// expander_utils2.c
char	*get_without_escape_str(char *escaped_str);
#endif
