/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:02:27 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:02:27 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_err.h"

void	err_put_tokenizer_unclosed_quote_err(void)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putendl_fd(ERR_SYNTAX_UNCLOSE_QUOTE, STDERR_FILENO);
}

void	err_put_parser_syntax_err(char *token)
{
	ft_putstr_fd(ERR_PREFIX, STDERR_FILENO);
	ft_putstr_fd(ERR_SYNTAX_MSG, STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}
