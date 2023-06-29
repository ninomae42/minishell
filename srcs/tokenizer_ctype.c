/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_ctype.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:07:21 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:07:22 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '|'
		|| c == '<' || c == '>');
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_redirect_character(char c)
{
	return (c == '<' || c == '>');
}

bool	is_pipeline_character(char c)
{
	return (c == '|');
}
