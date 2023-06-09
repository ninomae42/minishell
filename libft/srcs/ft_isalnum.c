/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:54:12 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 10:28:38 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// alphanumeric character test
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}
