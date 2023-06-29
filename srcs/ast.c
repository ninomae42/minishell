/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:59:09 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 09:59:10 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_ast	*new_ast(void)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (ast == NULL)
		err_fatal(errno);
	ast->root = NULL;
	return (ast);
}

t_ast_node	*new_ast_node(t_node_kind kind, t_ast_node *child,
		t_ast_node *brother, char *word)
{
	t_ast_node	*node;

	node = (t_ast_node *)malloc(sizeof(t_ast_node));
	if (node == NULL)
		err_fatal(errno);
	node->kind = kind;
	node->child = child;
	node->brother = brother;
	if (word != NULL)
	{
		node->literal = ft_strdup(word);
		if (node->literal == NULL)
			err_fatal(errno);
	}
	else
		node->literal = NULL;
	return (node);
}

void	ast_destroy(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ast_node_destroy(ast->root);
	free(ast);
}

void	ast_node_destroy(t_ast_node *node)
{
	t_ast_node	*child;
	t_ast_node	*brother;

	if (node == NULL)
		return ;
	child = node->child;
	brother = node->brother;
	ast_node_destroy(child);
	ast_node_destroy(brother);
	free(node->literal);
	free(node);
}
