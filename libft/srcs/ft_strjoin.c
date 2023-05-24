/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:59:12 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:46:20 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

// Allocates and returns a new string, whici is the result of
// the concatenation of s1 and s2.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p_ret;
	size_t	alloc_size;

	if (s1 == NULL && s2 == NULL)
		return (ft_strdup(""));
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	alloc_size = sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1);
	p_ret = (char *)malloc(alloc_size);
	if (p_ret == NULL)
		return (NULL);
	ft_strlcpy(p_ret, s1, alloc_size);
	ft_strlcat(p_ret, s2, alloc_size);
	return (p_ret);
}
