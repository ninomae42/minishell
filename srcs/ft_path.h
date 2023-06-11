#ifndef FT_PATH_H
# define FT_PATH_H
# include <errno.h>
# include <sys/stat.h>
# include "minishell.h"
# include "libft.h"

# define DIR_DELIMITER ':'

// path_executable.c
char	*path_search_binary_path(char *search_dir, char *filename);

// path_dir_split.c
char	**path_dir_split(char *dir_list);
void	dir_free(char **dirs);
void	dir_print(char **dir);

// path_utils.c
bool	path_is_contain_slash(char *path);
bool	path_is_directory(char *path);
bool	path_is_exist(char *path);

#endif
