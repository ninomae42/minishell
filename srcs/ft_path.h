#ifndef FT_PATH_H
# define FT_PATH_H
# include <errno.h>
# include "minishell.h"
# include "libft.h"

// path_dir_split.c
char	**path_split_dirs(char *env_path);
void	dir_free(char **dir);
void	dir_print(char **dir);

#endif
