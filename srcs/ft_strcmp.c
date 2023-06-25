#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p_s1;
	const unsigned char	*p_s2;
	size_t				i;

	p_s1 = (const unsigned char *)s1;
	p_s2 = (const unsigned char *)s2;
	i = 0;
	while (p_s1[i] && p_s2[i])
	{
		if (p_s1[i] != p_s2[i])
			return (p_s1[i] - p_s2[i]);
		i++;
	}
	return (p_s1[i] - p_s2[i]);
}
