/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:58:23 by tashimiz          #+#    #+#             */
/*   Updated: 2022/06/25 15:44:17 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_internal.h"

static size_t	count_strs(char const *s, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			cnt++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (cnt);
}

static size_t	len_til_delm(char const *s, unsigned int loc, char c)
{
	size_t	len;

	len = 0;
	while (s[loc] != '\0' && s[loc] != c)
	{
		len++;
		loc++;
	}
	return (len);
}

static int	check_and_free(char **arr_2d, size_t arr_num)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (arr_2d[cnt] != NULL)
		cnt++;
	if (cnt + 1 < arr_num)
	{
		while (i < arr_num)
		{
			free(arr_2d[i]);
			i++;
		}
		free(arr_2d);
		return (1);
	}
	return (0);
}

static char	**split_main(char const *s, char c)
{
	char	**p_ret;
	size_t	i;
	size_t	arr;

	p_ret = (char **)malloc(sizeof(char *) * (count_strs(s, c) + 1));
	if (p_ret == NULL)
		return (NULL);
	p_ret[count_strs(s, c)] = NULL;
	i = 0;
	arr = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			p_ret[arr] = ft_substr(s, i, len_til_delm(s, i, c));
			arr++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (p_ret);
}

// Allocates and returns an array of strings obtained by splitting
// 's' using the character 'c' as a delimiter. The array must be
// ended by a NULL pointer.
char	**ft_split(char const *s, char c)
{
	char	**p_ret;

	if (s == NULL)
		return (NULL);
	else if (s[0] == '\0' && c == '\0')
	{
		p_ret = (char **)malloc(sizeof(char *) * 1);
		p_ret[0] = NULL;
		return (p_ret);
	}
	p_ret = split_main(s, c);
	if (p_ret == NULL)
		return (NULL);
	if (check_and_free(p_ret, count_strs(s, c) + 1))
		return (NULL);
	return (p_ret);
}
