#include "expander.h"

// concat two strings. This fucntion FREES s1 and s2
char	*concat_str(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (res == NULL)
		err_fatal(errno);
	free(s1);
	free(s2);
	return (res);
}

bool	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

char	*expand_no_quote(char **word)
{
	char	*iword;
	char	*save_iword;
	char	*res;

	iword = *word;
	save_iword = iword;
	// while (*iword && !is_quote_char(*iword) && *iword != '$')
	while (*iword)
		iword++;
	*word = iword;
	res = ft_strndup(save_iword, iword - save_iword);
	if (res == NULL)
		err_fatal(errno);
	return (res);
}

char	*expand_word(char *word)
{
	char	*iword;
	char	*expanded;
	char	*value;

	expanded = NULL;
	value = NULL;
	iword = word;
	while (iword && *iword)
	{
		value = expand_no_quote(&iword);
		expanded = concat_str(expanded, value);
	}
	return (expanded);
}

static void	expand_internal(t_ast_node *node)
{
	t_ast_node	*child;
	t_ast_node	*brother;
	char		*expanded;

	if (node == NULL)
		return ;
	child = node->child;
	brother = node->brother;
	if (node->kind == ND_WORD && node->literal)
	{
		expanded = expand_word(node->literal);
		free(node->literal);
		node->literal = expanded;
	}
	expand_internal(child);
	expand_internal(brother);
}

void	expand(t_ast *ast)
{
	if (ast == NULL)
		return ;
	expand_internal(ast->root);
}
