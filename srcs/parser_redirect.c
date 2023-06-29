/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:06:03 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:06:03 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define REDIRECT_IN 1
#define REDIRECT_IN_HDOC 2
#define REDIRECT_OUT 3
#define REDIRECT_OUT_APPEND 4

int	p_get_redirect_type(t_parser *p)
{
	if (p_cur_is(p, TK_REDIRECT_IN))
		return (REDIRECT_IN);
	else if (p_cur_is(p, TK_REDIRECT_IN_HDOC))
		return (REDIRECT_IN_HDOC);
	else if (p_cur_is(p, TK_REDIRECT_OUT))
		return (REDIRECT_OUT);
	return (REDIRECT_OUT_APPEND);
}

t_ast_node	*parse_redirect_main(t_parser *p, t_node_kind kind)
{
	t_ast_node	*node;

	node = new_ast_node(kind, NULL, NULL, NULL);
	p_next_token(p);
	if (!p_cur_is(p, TK_WORD))
	{
		err_put_parser_syntax_err(p->cur_tok->literal);
		p->is_syntax_err = true;
		free(node);
		return (NULL);
	}
	node->literal = ft_strdup(p->cur_tok->literal);
	if (node->literal == NULL)
		err_fatal(errno);
	p_next_token(p);
	return (node);
}

t_ast_node	*parse_redirect(t_parser *p)
{
	t_ast_node	*node;
	int			redirect_type;

	redirect_type = p_get_redirect_type(p);
	node = NULL;
	if (redirect_type == REDIRECT_IN)
		node = parse_redirect_main(p, ND_REDIRECT_IN);
	else if (redirect_type == REDIRECT_IN_HDOC)
		node = parse_redirect_main(p, ND_REDIRECT_IN_HDOC);
	else if (redirect_type == REDIRECT_OUT)
		node = parse_redirect_main(p, ND_REDIRECT_OUT);
	else if (redirect_type == REDIRECT_OUT_APPEND)
		node = parse_redirect_main(p, ND_REDIRECT_OUT_APPEND);
	return (node);
}
