/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:06:37 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:06:38 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_path.h"

bool	path_is_contain_slash(char *path)
{
	if (*path != '\0' && ft_strchr(path, '/') != NULL)
		return (true);
	return (false);
}

bool	path_is_directory(char *path)
{
	struct stat	st;

	errno = 0;
	if (stat(path, &st) < 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

bool	path_is_exist(char *path)
{
	errno = 0;
	if (access(path, F_OK) < 0)
		return (false);
	return (true);
}

bool	path_has_exec_right(char *path)
{
	errno = 0;
	if (access(path, X_OK) < 0)
		return (false);
	return (true);
}

char	*concat_path(char *dir, char *filename)
{
	size_t	path_len;
	char	*path;

	path_len = ft_strlen(dir) + ft_strlen(filename) + 2;
	path = (char *)malloc(sizeof(char) * path_len);
	if (path == NULL)
		err_fatal(errno);
	ft_strlcpy(path, dir, path_len);
	ft_strlcat(path, "/", path_len);
	ft_strlcat(path, filename, path_len);
	return (path);
}
