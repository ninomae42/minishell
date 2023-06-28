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
		if (*iword == '\'')
			value = expand_single_quote(&iword);
		else if (*iword == '"')
			value = expand_double_quote(&iword);
		else if (*iword == '$')
			value = expand_parameter(&iword);
		else
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
	char		*tmp;

	if (node == NULL)
		return ;
	child = node->child;
	brother = node->brother;
	if (node->kind == ND_WORD && node->literal)
	{
		expanded = expand_word(node->literal);
		tmp = get_without_escape_str(expanded);
		free(expanded);
		expanded = tmp;
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
