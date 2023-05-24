/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:59:58 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:47:11 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

// Applies the function 'f' to each character of the string 's',
// and passing its index as first argument to create a new string
// resulting from successive applications of 'f'.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p_ret;
	size_t	cnt;

	if (s == NULL || f == NULL)
		return (NULL);
	if (ft_strlen(s) > UINT_MAX)
		return (NULL);
	p_ret = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (p_ret == NULL)
		return (NULL);
	cnt = 0;
	while (s[cnt] != '\0')
	{
		p_ret[cnt] = f((unsigned int)cnt, s[cnt]);
		cnt++;
	}
	p_ret[cnt] = '\0';
	return (p_ret);
}
