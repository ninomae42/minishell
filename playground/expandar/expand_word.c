#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	alloc_size;
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (strdup(""));
	else if (s1 == NULL)
		return (strdup(s2));
	else if (s2 == NULL)
		return (strdup(s1));
	alloc_size = strlen(s1) + strlen(s2) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	strlcpy(res, s1, alloc_size);
	strlcat(res, s2, alloc_size);
	return (res);
}

char	*ft_strcat(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	if (res == NULL)
		exit(EXIT_FAILURE);
	free(s1);
	free(s2);
	return (res);
}

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}
bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

size_t	strlen_with_escape(char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '"')
			len++;
		len++;
		s++;
	}
	return (len);
}

void	copy_str_with_escape(char *dst, char *src)
{
	while (*src)
	{
		if (*src == '\'' || *src == '"')
			*dst++ = '\\';
		*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_escaped_str(char *s)
{
	size_t	len;
	char	*res;

	if (s == NULL)
		return (NULL);
	len = strlen_with_escape(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		exit(EXIT_FAILURE);
	copy_str_with_escape(res, s);
	return (res);
}

typedef enum e_expand_state
{
	E_NORMAL,
	E_SINGLE,
	E_DOUBLE,
}	t_expa_state;

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
	res = strndup(save_iword, iword - save_iword);
	if (res == NULL)
		exit(EXIT_FAILURE);
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
	res = strndup(save_iword, iword - save_iword);
	if (res == NULL)
		exit(EXIT_FAILURE);
	iword++;
	*word = iword;
	return (res);
}

char	*expand_parameter(char **word)
{
	char	*i_word;
	char	*save_word;
	char	*name;
	char	*value;

	i_word = *word;
	i_word++;
	save_word = i_word;
	// validate identifier or not
	while (*i_word && is_alpha_num_under(*i_word))
		i_word++;
	*word = i_word;

	name = strndup(save_word, i_word - save_word);
	if (name == NULL)
		exit(EXIT_FAILURE);
	// printf("name: [%s]\n", name);
	value = getenv(name);
	free(name);
	if (value == NULL)
		return (NULL);
	// printf("value: %s\n", value);
	value = get_escaped_str(value);
	if (value == NULL)
		exit(EXIT_FAILURE);
	// printf("value: %s\n", value);
	return (value);
}

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
	res = strndup(save_word, iword - save_word);
	if (res == NULL)
		exit(EXIT_FAILURE);
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
		res = ft_strcat(res, value);
	}
	iword++;
	*word = iword++;
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
		if (*iword == '$')
			value = expand_parameter(&iword);
		else if (*iword == '\'')
			value = expand_single_quote(&iword);
		else if (*iword == '"')
			value = expand_double_quote(&iword);
		else
			value = expand_no_quote(&iword);
		expanded = ft_strcat(expanded, value);
	}
	return (expanded);
}

// hogehoge
//
// 'hoge hoge'
// '$USER'
//
// aa'$USER'"$USER"bb
// "hoge hoge"
// "hoge hoge"


int	main(int argc, char **argv)
{
	char	*word;
	char	*expanded_word;

	if (argc != 2)
		exit(EXIT_FAILURE);
	word = argv[1];
	word = strdup(word);
	printf("input: [%s]\n", word);
	expanded_word = expand_word(word);
	printf("expand: [%s]\n", expanded_word);
	free(expanded_word);
	free(word);
	exit(EXIT_SUCCESS);
}
