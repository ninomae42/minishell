/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:59:03 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:46:09 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	cnt;

	if (s == NULL || f == NULL)
		return ;
	if (ft_strlen(s) > UINT_MAX)
		return ;
	cnt = 0;
	while (s[cnt] != '\0')
	{
		f((unsigned int)cnt, &s[cnt]);
		cnt++;
	}
}
