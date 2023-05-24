/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:00:44 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:47:58 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

// allocates and returns a copy of 's1' with the characters
// specified in 'set' removed from the beginning and
// the end of the string.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_ret;
	char	*s1_front;
	char	*s1_back;
	size_t	alloc_size;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s1_front = (char *)s1;
	while (ft_strchr(set, *s1_front) != NULL && *s1_front != '\0')
		s1_front++;
	if (ft_strlen(s1_front) == 0)
		return (ft_strdup(""));
	s1_back = s1_front + ft_strlen(s1_front) - 1;
	while (ft_strchr(set, *s1_back) != NULL && s1_front != s1_back)
		s1_back--;
	alloc_size = sizeof(char) * ((s1_back - s1_front + 1) + 1);
	p_ret = (char *)malloc(alloc_size);
	if (p_ret == NULL)
		return (NULL);
	ft_strlcpy(p_ret, s1_front, alloc_size);
	return (p_ret);
}
