/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_pipeline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:07:32 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:07:32 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

bool	t_is_pipeline(t_tokenizer *tokenizer)
{
	return (is_pipeline_character(tokenizer->cur));
}

t_token_node	*t_tokenize_pipeline(t_tokenizer *tokenizer)
{
	t_token_node	*node;

	node = new_token_node(TK_PIPELINE, ft_strdup("|"));
	t_read_char(tokenizer);
	return (node);
}
