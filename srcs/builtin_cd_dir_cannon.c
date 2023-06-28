#include "builtin.h"
#include "ft_path.h"

char	*get_parent_dir(char *path)
{
	char	*parent;
	char	*last_slash;

	last_slash = ft_strrchr(path, '/');
	if (last_slash == NULL || last_slash == path)
		parent = ft_strdup("/");
	else
		parent = ft_strndup(path, last_slash - path);
	if (parent == NULL)
		err_fatal(errno);
	return (parent);
}

void	update_path(char **path, char *dir_component)
{
	char	*tmp;

	if (ft_strcmp(dir_component, ".") == 0)
		return ;
	else if (ft_strcmp(dir_component, "..") == 0)
	{
		tmp = *path;
		*path = get_parent_dir(*path);

		free(tmp);
	}
	else
	{
		tmp = *path;
		*path = concat_path(*path, dir_component);
		free(tmp);
	}
}

void	split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

char	*get_cannoned_path(char *cur_path)
{
	char	**dirs;
	char	*res_path;
	size_t	i;

	dirs = ft_split(cur_path, '/');
	if (dirs == NULL)
		err_fatal(errno);
	res_path = ft_strdup("/");
	if (res_path == NULL)
		err_fatal(errno);
	i = 0;
	while (dirs[i])
	{
		update_path(&res_path, dirs[i++]);
		if (!path_is_directory(res_path))
		{
			free(res_path);
			split_free(dirs);
			return (NULL);
		}
	}
	split_free(dirs);
	return (res_path);
}
