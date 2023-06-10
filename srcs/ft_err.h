#ifndef FT_ERR_H
# define FT_ERR_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

#define ERR_PREFIX "minishell: "

// err_main.c
void	err_puterr(char *err_msg);
void	ft_fatal(char *func_name);

#endif
