#ifndef FT_ERR_H
# define FT_ERR_H
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

# define ERR_PREFIX "minishell: "
# define ERR_CD_PREFIX "cd: "
# define ERR_IS_DIRECTORY "is a directory"
# define COMMAND_NOT_FOUND "command not found"
# define ERR_SYNTAX_MSG "syntax error near unexpected token `"
# define ERR_INVALID_ENV_IDENT "not a valid identifier"
# define ERR_SYNTAX_UNCLOSE_QUOTE "syntax error: unclosed quote"
# define ERR_IDENT_INVALID "not a valid identifier"
# define ERR_AMBIGUOUS_REDIRECT "ambiguous redirect"

// err_main.c
void	err_puterr(char *err_msg);
void	ft_fatal(char *func_name);
void	err_fatal(int err_no);
void	err_perror(int err_no);
void	err_perror_with_path(int err_no, char *path);
void	err_put_tokenizer_unclosed_quote_err(void);

// err_exec.c
void	err_is_directory(char *path);
void	err_command_not_found(char *command_name);
void	err_ambiguous_redirect(char *filename);

// err_parser.c
void	err_put_parser_syntax_err(char *token);

// err_builtin.c
void	err_identifier(char *command_name, char *identifier);
void	err_builtin_exit(char *err_msg, char *arg);
void	err_builtin_cd_perror_with_path(int err_no, char *path);
void	err_builtin_cd(char *err_msg);
void	err_env_name_not_valid(char *env_str);

#endif
