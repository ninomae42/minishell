/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_dir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:06:31 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:06:32 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_path.h"

void	dir_print(char **dirs)
{
	size_t	i;

	i = 0;
	while (dirs[i])
	{
		printf("%s\n", dirs[i]);
		i++;
	}
}

size_t	dir_len(char **dirs)
{
	size_t	len;

	len = 0;
	while (dirs[len])
		len++;
	return (len);
}
