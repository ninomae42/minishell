#include "expander.h"

char	*duplicate_within_dquote(char **word)
{
	char	*iword;
	char	*save_word;
	char	*res;

	iword = *word;
	save_word = iword;
	res = NULL;
	while (iword && *iword && *iword != '"' && *iword != '$')
		iword++;
	res = ft_strndup(save_word, iword - save_word);
	if (res == NULL)
		err_fatal(errno);
	*word = iword;
	return (res);
}

char	*expand_double_quote(char **word)
{
	char	*iword;
	char	*res;
	char	*value;

	iword = *word;
	iword++;
	res = NULL;
	value = NULL;
	while (*iword && *iword != '"')
	{
		if (*iword == '$')
			value = expand_parameter(&iword);
		else
			value = duplicate_within_dquote(&iword);
		res = concat_str(res, value);
	}
	iword++;
	*word = iword++;
	return (res);
}
