#include "exec.h"

char	*concat_path_and_file(char *env_path_entry, char *filename)
{
	size_t	alloc_size;
	char	*path;

	alloc_size = ft_strlen(env_path_entry) + 1 + ft_strlen(filename) + 1;
	path = (char *)malloc(sizeof(char) * alloc_size);
	if (path == NULL)
		perror_exit("malloc");
	ft_strlcpy(path, env_path_entry, alloc_size);
	ft_strlcat(path, "/", alloc_size);
	ft_strlcat(path, filename, alloc_size);
	return (path);
}

void	ft_split_free(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*get_executable_path(char *env_path, char *filename)
{
	size_t	i;
	char	**res_split;
	char	*path;

	res_split = ft_split(env_path, ':');
	if (res_split == NULL)
		return (NULL);
	i = 0;
	while (res_split[i] != NULL)
	{
		path = concat_path_and_file(res_split[i], filename);
		if (access(path, X_OK) == 0)
		{
			ft_split_free(res_split);
			return (path);
		}
		free(path);
		i++;
	}
	ft_split_free(res_split);
	return (NULL);
}

char	*find_executable_path(char *filename, t_env *env)
{
	char	*env_path;
	char	*executable_path;

	if (strchr(filename, '/') != NULL) 
		return (filename);
	env_path = ft_getenv(env, "PATH");
	executable_path = get_executable_path(env_path, filename);
	if (executable_path == NULL)
		return (filename);
	return (executable_path);
}
