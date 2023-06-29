/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:04:34 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:04:35 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || ft_isdigit(c));
}

static size_t	strlen_with_escape(char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			len++;
		len++;
		s++;
	}
	return (len);
}

static void	copy_str_with_escape(char *dst, char *src)
{
	while (*src)
	{
		if (*src == '\'' || *src == '"')
			*dst++ = '\\';
		*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_escaped_str(char *s)
{
	size_t	len;
	char	*res;

	if (s == NULL)
		return (NULL);
	len = strlen_with_escape(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		err_fatal(errno);
	copy_str_with_escape(res, s);
	return (res);
}
