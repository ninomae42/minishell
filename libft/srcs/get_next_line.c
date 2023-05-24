/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:20:44 by tashimiz          #+#    #+#             */
/*   Updated: 2022/11/25 17:20:45 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

#define MAX_FD 256
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 256
#endif

// create a line from the string passed by an argument.
static char	*create_line(const char *save)
{
	char	*p_line;
	size_t	i;

	i = 0;
	if (save[i] == '\0')
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	p_line = (char *)malloc(sizeof(char) * (i + 1 + 1));
	if (p_line == NULL)
		return (NULL);
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
	{
		p_line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		p_line[i] = save[i];
		i++;
	}
	p_line[i] = '\0';
	return (p_line);
}

// read from fd to buffer, and save it to static variable 'save'.
static char	*read_from_fd_and_save(int fd, char *save)
{
	char	*buf;
	char	*p_save_free;
	ssize_t	bytes_read;

	buf = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	bytes_read = 1;
	while (save == NULL || (ft_strchr(save, '\n') == NULL && bytes_read != 0))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		p_save_free = save;
		save = ft_strjoin(save, buf);
		free(p_save_free);
		p_save_free = NULL;
	}
	free(buf);
	return (save);
}

// trim the line that is in variable 'line' and creates copy of save
static char	*trim_line_in_save(char *save)
{
	char	*p_ret;
	size_t	i;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	p_ret = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (p_ret == NULL)
		return (NULL);
	i++;
	ft_strlcpy(p_ret, &save[i], ft_strlen(save) - i + 1);
	free(save);
	return (p_ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*fds[MAX_FD];

	if (fd < 0 || MAX_FD < fd || BUFFER_SIZE <= 0)
		return (NULL);
	fds[fd] = read_from_fd_and_save(fd, fds[fd]);
	if (fds[fd] == NULL)
		return (NULL);
	line = create_line(fds[fd]);
	fds[fd] = trim_line_in_save(fds[fd]);
	return (line);
}
