#include "ft_path.h"

static size_t	find_num_of_dirs(char *dir_list);
static char		*find_next_delim(char *str);
static char		**split_main(char *str, size_t num_of_dirs);

// Receive a colon(":") separated dir_list.
// On success splitted directory list is returned,
// Otherwise, NULL is returned.
char	**path_dir_split(char *dir_list)
{
	char	**dirs;
	size_t	num_of_dirs;

	if (dir_list == NULL)
		return (NULL);
	num_of_dirs = find_num_of_dirs(dir_list);
	dirs = split_main(dir_list, num_of_dirs);
	return (dirs);
}

void	dir_free(char **dirs)
{
	size_t	i;

	i = 0;
	while (dirs[i] != NULL)
	{
		free(dirs[i]);
		i++;
	}
	free(dirs);
}

static size_t	find_num_of_dirs(char *s)
{
	size_t	num_of_dirs;

	num_of_dirs = 1;
	while (*s)
	{
		if (*s == DIR_DELIMITER)
			num_of_dirs++;
		s++;
	}
	return (num_of_dirs);
}

static char	*find_next_delim(char *s)
{
	char	*delim;

	delim = ft_strchr(s, DIR_DELIMITER);
	if (delim == NULL)
		delim = ft_strchr(s, '\0');
	return (delim);
}

static char	**split_main(char *s, size_t num_of_dirs)
{
	char	**dirs;
	char	*delim;
	size_t	i;

	dirs = (char **)malloc(sizeof(char *) * (num_of_dirs + 1));
	if (dirs == NULL)
		return (NULL);
	i = 0;
	ft_bzero(dirs, sizeof(char *) * (num_of_dirs + 1));
	dirs[num_of_dirs] = NULL;
	while (i < num_of_dirs)
	{
		delim = find_next_delim(s);
		dirs[i] = ft_strndup(s, delim - s);
		if (dirs[i] ==  NULL)
		{
			dir_free(dirs);
			return (NULL);
		}
		s = delim + 1;
		i++;
	}
	return (dirs);
}
