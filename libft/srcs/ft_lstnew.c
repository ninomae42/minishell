/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:56:21 by tashimiz          #+#    #+#             */
/*   Updated: 2022/03/19 14:58:58 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*p_lst;

	p_lst = (t_list *)malloc(sizeof(t_list) * 1);
	if (p_lst == NULL)
		return (NULL);
	p_lst->content = content;
	p_lst->next = NULL;
	return (p_lst);
}
