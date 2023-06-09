/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 17:00:34 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 15:02:20 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// locate character in string
char	*ft_strrchr(const char *s, int c)
{
	char	*p_s;

	p_s = (char *)s;
	p_s = p_s + ft_strlen(p_s);
	while (p_s != s)
	{
		if (*p_s == (char)c)
			return (p_s);
		p_s--;
	}
	if (*p_s == (char)c)
		return (p_s);
	return (NULL);
}
