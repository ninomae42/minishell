#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}
bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

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

size_t	strlen_without_escape(char *escaped_str)
{
	size_t	len;

	len = 0;
	while (*escaped_str)
	{
		if (*escaped_str == '\\')
			escaped_str++;
		if (*escaped_str == '\0')
			return (len);
		len++;
		escaped_str++;
	}
	return (len);
}

void	copy_str_without_escape(char *dst, char *src)
{
	while (*src)
	{
		if (*src == '\\')
			src++;
		if (*src == '\0')
			break ;
		*dst++ = *src++;
	}
	*dst = '\0';
}

char	*get_without_escape_str(char *escaped_str)
{
	size_t	len;
	char	*res;

	if (escaped_str == NULL)
		return (NULL);
	len = strlen_without_escape(escaped_str);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		exit(EXIT_FAILURE);
	copy_str_without_escape(res, escaped_str);
	return (res);
}

char	*expand_parameter(char **word)
{
	char	*i_word;
	char	*save_word;
	char	*name;
	char	*value;

	i_word = *word;
	save_word = i_word;
	while (is_alpha_num_under(*i_word))
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
	printf("value: %s\n", value);
	value = get_escaped_str(value);
	if (value == NULL)
		exit(EXIT_FAILURE);
	// printf("value: %s\n", value);
	return (value);
}

char	*copy_word(char **word)
{
	char	*i_word;
	char	*save_word;
	char	*res;

	i_word = *word;
	save_word = i_word;
	while (*i_word && *i_word != '$')
		i_word++;
	*word = i_word;
	res = strndup(save_word, i_word - save_word);
	if (res == NULL)
		exit(EXIT_FAILURE);
	return (res);
}

char	*expand_word(char *word)
{
	char	*iword;
	char	*expanded;
	char	*tmp;
	char	*value;

	iword = word;
	expanded = NULL;
	while (*iword)
	{
		if (*iword == '$')
		{
			iword++;
			value = expand_parameter(&iword);
		}
		else
		{
			value = copy_word(&iword);
		}
		tmp = ft_strjoin(expanded, value);
		free(value);
		free(expanded);
		expanded = tmp;
	}
	return (expanded);
}

size_t	strlen_without_quote(char *quoted_str, char quote)
{
	size_t	len;

	len = 0;
	while (*quoted_str)
	{
		if (*quoted_str == '\\' && *(quoted_str + 1))
		{
			quoted_str += 2;
			continue ;
		}
		if (*quoted_str == quote)
		{
			quoted_str++;
			continue ;
		}
		len++;
		quoted_str++;
	}
	return (len);
}

void	copy_str_without_quote(char *dst, char *quoted_str, char quote)
{
	while (*quoted_str)
	{
		if (*quoted_str == '\\' && *(quoted_str + 1))
		{
			quoted_str += 2;
			continue;
		}
		if (*quoted_str == quote)
		{
			quoted_str++;
			continue ;
		}
		*dst++ = *quoted_str++;
	}
	*dst = '\0';
}

char	*quote_removal(char *quoted_str, char quote)
{
	size_t	len;
	char	*res;

	if (quoted_str == NULL)
		return (NULL);
	len = strlen_without_quote(quoted_str, quote);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		exit(EXIT_FAILURE);
	copy_str_without_quote(res, quoted_str, quote);
	return (res);
}

int	main(int argc, char **argv)
{
	char	*word;
	char	*expanded_word;

	if (argc != 2)
		exit(EXIT_FAILURE);
	word = argv[1];
	printf("name:[%s]\n", word);

	expanded_word = expand_word(word);
	printf("expanded:[%s]\n", expanded_word);

	char	*tmp = get_without_escape_str(expanded_word);
	printf("expanded2:[%s]\n", tmp);

	char	*tmp2 = quote_removal(tmp, '\'');
	printf("quote removed:[%s]\n", tmp2);

	free(tmp);
	free(tmp2);
	free(expanded_word);

	exit(EXIT_SUCCESS);
}
