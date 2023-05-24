/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:57:27 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 14:59:56 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// fill a byte string with a byte value
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			cnt;
	unsigned char	*p_b;

	p_b = (unsigned char *)b;
	cnt = 0;
	while (cnt < len)
		p_b[cnt++] = (unsigned char)c;
	return (b);
}
