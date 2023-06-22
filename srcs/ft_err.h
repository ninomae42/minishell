#ifndef FT_ERR_H
# define FT_ERR_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

# define ERR_PREFIX "minishell: "
# define ERR_IS_DIRECTORY "is a directory"
# define COMMAND_NOT_FOUND "command not found"
# define ERR_SYNTAX_MSG "syntax error near unexpected token `"

// err_main.c
void	err_puterr(char *err_msg);
void	ft_fatal(char *func_name);
void	err_fatal(int err_no);
void	err_perror(int err_no);
void	err_perror_with_path(int err_no, char *path);
void	err_is_directory(char *path);
void	err_command_not_found(char *command_name);

// err_parser.c
void	err_put_parser_syntax_err(char *token);;

#endif
