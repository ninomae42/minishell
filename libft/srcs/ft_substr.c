/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:00:55 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:48:19 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

// Allocates and returns a substring from the string 's'.
// The substring begins at index 'start' and is of maximum size 'len'.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p_ret;
	size_t	s_len;
	size_t	allocsize;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0 || s_len <= (size_t)start)
		return (ft_strdup(""));
	if (s_len < len)
		allocsize = s_len + 1;
	else
		allocsize = len + 1;
	p_ret = (char *)malloc(sizeof(char) * (allocsize));
	if (p_ret == NULL)
		return (NULL);
	ft_strlcpy(p_ret, &s[start], allocsize);
	return (p_ret);
}
