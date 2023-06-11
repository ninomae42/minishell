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

// ft_strndup.c
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strndup(char *s, size_t len);

#endif
