/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:03:29 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:03:30 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*search_binary_internal(char **dirs, char *filename)
{
	char	*path;

	while (*dirs)
	{
		if (*dirs[0] == '\0')
			path = concat_path(".", filename);
		else
			path = concat_path(*dirs, filename);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	return (NULL);
}

char	*build_binary_path(char *search_dir, char *filename)
{
	char	**dirs;
	char	*res_path;

	if (*filename == '\0')
		return (ft_strdup(""));
	dirs = path_dir_split(search_dir);
	if (dirs == NULL)
		err_fatal(errno);
	res_path = search_binary_internal(dirs, filename);
	dir_free(dirs);
	return (res_path);
}
