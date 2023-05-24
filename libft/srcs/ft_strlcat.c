/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:59:24 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 15:01:37 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// find length of string
static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = ft_strlen(s);
	if (len < maxlen)
		return (len);
	else
		return (maxlen);
}

// size-bounded string concatenation
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_nlen;
	size_t	src_len;
	size_t	cpy_cnt;

	if (dstsize == 0 && dst == NULL)
		return (ft_strlen(src));
	dst_nlen = ft_strnlen(dst, dstsize);
	src_len = ft_strlen(src);
	if (dstsize <= ft_strlen(dst))
		return (dst_nlen + src_len);
	cpy_cnt = dstsize - ft_strlen(dst) - 1;
	while (*dst != '\0')
		dst++;
	while (*src != '\0' && cpy_cnt > 0)
	{
		*dst = *src;
		dst++;
		src++;
		cpy_cnt--;
	}
	*dst = '\0';
	return (dst_nlen + src_len);
}
