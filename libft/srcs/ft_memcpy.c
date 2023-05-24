/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:57:03 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 14:59:42 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy memory area
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	p_dst = (unsigned char *)dst;
	p_src = (const unsigned char *)src;
	i = 0;
	while (dst != src && i < n)
	{
		p_dst[i] = p_src[i];
		i++;
	}
	return (dst);
}
