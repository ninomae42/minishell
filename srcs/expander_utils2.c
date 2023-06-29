/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:04:42 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:04:42 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	strlen_without_escape(char *escaped_str)
{
	size_t	len;

	len = 0;
	while (*escaped_str)
	{
		if (*escaped_str == '\\')
			escaped_str++;
		if (*escaped_str == '\0')
			return (len);
		len++;
		escaped_str++;
	}
	return (len);
}

static void	copy_str_without_escape(char *dst, char *src)
{
	while (*src)
	{
		if (*src == '\\')
			src++;
		if (*src == '\0')
			break ;
		*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_without_escape_str(char *escaped_str)
{
	size_t	len;
	char	*res;

	if (escaped_str == NULL)
		return (NULL);
	len = strlen_without_escape(escaped_str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		err_fatal(errno);
	copy_str_without_escape(res, escaped_str);
	return (res);
}
