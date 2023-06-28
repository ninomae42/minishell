#include "expander.h"

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
	while (*iword && !is_quote_char(*iword) && *iword != '$')
		iword++;
	*word = iword;
	res = ft_strndup(save_iword, iword - save_iword);
	if (res == NULL)
		err_fatal(errno);
	return (res);
}

char	*expand_single_quote(char **word)
{
	char	*iword;
	char	*save_iword;
	char	*res;

	iword = *word;
	iword++;
	save_iword = iword;
	while (*iword && *iword != '\'')
		iword++;
	res = ft_strndup(save_iword, iword - save_iword);
	if (res == NULL)
		err_fatal(errno);
	iword++;
	*word = iword;
	return (res);
}
