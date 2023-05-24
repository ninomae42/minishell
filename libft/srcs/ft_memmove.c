/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:57:13 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 14:59:50 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy byte string
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	if (dst == src || len == 0)
		return (dst);
	p_dst = (unsigned char *)dst;
	p_src = (const unsigned char *)src;
	if (dst < src)
		while (len--)
			*p_dst++ = *p_src++;
	else
	{
		p_dst += len - 1;
		p_src += len - 1;
		while (len--)
			*p_dst-- = *p_src--;
	}
	return (dst);
}
