/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:58:44 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 15:01:15 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// locate character in string
char	*ft_strchr(const char *s, int c)
{
	char	*p_s;

	p_s = (char *)s;
	while (*p_s != '\0')
	{
		if (*p_s == (char)c)
			return (p_s);
		p_s++;
	}
	if ((char)c == '\0')
		return (p_s);
	return (NULL);
}
