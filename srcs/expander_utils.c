#include "expander.h"
static size_t	strlen_with_escape(char *s)
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

static void	copy_str_with_escape(char *dst, char *src)
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
		err_fatal(errno);
	copy_str_with_escape(res, s);
	return (res);
}
