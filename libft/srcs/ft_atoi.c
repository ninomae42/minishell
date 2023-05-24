/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:53:38 by tashimiz          #+#    #+#             */
/*   Updated: 2022/11/25 19:04:15 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

// white-space character test
static int	ft_isspace(int c)
{
	return (('\t' <= c && c <= '\r') || c == ' ');
}

// overflow check
static int	is_overflow(long current, long sign, char next)
{
	if (0 < sign)
	{
		if (LONG_MAX / 10 < current)
			return (1);
		current = current * 10;
		if ((LONG_MAX - current) < (next - '0'))
			return (1);
	}
	else
	{
		current = current * (-1);
		if (current < (LONG_MIN / 10))
			return (1);
		current = current * 10;
		if (-(next - '0') < (LONG_MIN - current))
			return (1);
	}
	return (0);
}

// main conversion logic
static long	do_conversion(const char *nptr, long sign, int *is_err)
{
	long	ret;

	ret = 0;
	while (ft_isdigit(*nptr))
	{
		if (is_overflow(ret, sign, *nptr))
		{
			*is_err = 1;
			if (0 < sign)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		ret = ret * 10 + (*nptr - '0');
		nptr++;
	}
	return (ret);
}

// convert ASCII string to integer
int	ft_atoi(const char *nptr)
{
	long	ret;
	long	sign;
	int		is_err;

	sign = 1;
	ret = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	if (!ft_isdigit(*nptr))
	{
		errno = EINVAL;
		return ((int)ret);
	}
	is_err = 0;
	ret = do_conversion(nptr, sign, &is_err);
	if (is_err)
	{
		errno = ERANGE;
		return ((int)ret);
	}
	return ((int)(sign * ret));
}
