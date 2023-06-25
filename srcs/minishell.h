#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "ft_err.h"
# include "env.h"

t_env	*g_env;

// ft_strndup.c
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strndup(char *s, size_t len);

// ft_strcmp.c
int		ft_strcmp(const char *s1, const char *s2);;

#endif
