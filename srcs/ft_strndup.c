/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:05:18 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:05:19 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (s[len] && len < maxlen)
		len++;
	return (len);
}

char	*ft_strndup(char *s, size_t len)
{
	char	*res;
	size_t	alloc_size;

	alloc_size = ft_strnlen(s, len) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (res == NULL)
		return (NULL);
	ft_strlcpy(res, s, alloc_size);
	return (res);
}
