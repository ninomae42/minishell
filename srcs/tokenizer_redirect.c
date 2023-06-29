/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:07:44 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:07:45 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

#define REDIRECT_IN 1
#define REDIRECT_IN_HDOC 2
#define REDIRECT_OUT 3
#define REDIRECT_OUT_APPEND 4

bool	t_is_redirect(t_tokenizer *tokenizer)
{
	return (is_redirect_character(tokenizer->cur));
}

static int	t_get_redirect_type(t_tokenizer	*tokenizer)
{
	if (tokenizer->cur == '<' && t_peek_char(tokenizer) == '<')
		return (REDIRECT_IN_HDOC);
	else if (tokenizer->cur == '>' && t_peek_char(tokenizer) == '>')
		return (REDIRECT_OUT_APPEND);
	else if (tokenizer->cur == '<')
		return (REDIRECT_IN);
	return (REDIRECT_OUT);
}

static t_token_node	*tokenize_redirect_main(t_tokenizer *tokenizer, int type)
{
	t_token_node	*node;

	node = NULL;
	if (type == REDIRECT_IN)
		node = new_token_node(TK_REDIRECT_IN, ft_strdup("<"));
	else if (type == REDIRECT_OUT)
		node = new_token_node(TK_REDIRECT_OUT, ft_strdup(">"));
	else if (type == REDIRECT_IN_HDOC)
		node = new_token_node(TK_REDIRECT_IN_HDOC, ft_strdup("<<"));
	else if (type == REDIRECT_OUT_APPEND)
		node = new_token_node(TK_REDIRECT_OUT_APPEND, ft_strdup(">>"));
	if (type == REDIRECT_IN_HDOC || type == REDIRECT_OUT_APPEND)
		t_read_char(tokenizer);
	t_read_char(tokenizer);
	return (node);
}

t_token_node	*t_tokenize_redirect(t_tokenizer *tokenizer)
{
	t_token_node	*node;
	int				redirect_type;

	redirect_type = t_get_redirect_type(tokenizer);
	node = tokenize_redirect_main(tokenizer, redirect_type);
	return (node);
}
