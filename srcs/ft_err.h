#ifndef FT_ERR_H
# define FT_ERR_H
# include <errno.h>
# include <unistd.h>
# include "libft.h"

#define ERR_PREFIX "minishell: "

// err_main.c
void	err_puterr(char *err_msg);

#endif
