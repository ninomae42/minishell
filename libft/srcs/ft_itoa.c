/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:59 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 14:58:05 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(int n)
{
	size_t	cnt;

	cnt = 0;
	if (n <= 0)
		cnt = 1;
	while (n != 0)
	{
		n /= 10;
		cnt++;
	}
	return (cnt);
}

static void	set_numbers(long int nbr, char *s, size_t cnt)
{
	if (nbr < 0)
	{
		nbr *= -1;
		s[0] = '-';
	}
	s[cnt] = "0123456789"[nbr % 10];
	if (nbr / 10)
		set_numbers(nbr / 10, s, --cnt);
}

// Allocates and returns a string representing the integer received
// as an argument. Negative numbers must be handled.
char	*ft_itoa(int n)
{
	char	*p_ret;

	p_ret = (char *)ft_calloc(count_digit(n) + 1, sizeof(char));
	if (p_ret == NULL)
		return (NULL);
	if (n == 0)
		p_ret[0] = '0';
	else
		set_numbers(n, p_ret, count_digit(n) - 1);
	return (p_ret);
}
