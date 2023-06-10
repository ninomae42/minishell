#ifndef FT_PATH_H
# define FT_PATH_H
# include <errno.h>
# include <sys/stat.h>
# include "minishell.h"
# include "libft.h"

// path_executable.c
char	*path_get_executable(char *filename);

// path_dir_split.c
char	**path_split_dirs(char *env_path);
void	dir_free(char **dir);
void	dir_print(char **dir);

// path_utils.c
bool	path_is_contain_slash(char *path);
bool	path_is_directory(char *path);
bool	path_is_exist(char *path);

#endif
