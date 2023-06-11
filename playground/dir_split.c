#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (s[len] && len < maxlen)
		len++;
	return (len);
}

char	*ft_strndup(char *s, size_t len)
{
	char	*res;
	size_t	alloc_size;

	alloc_size = ft_strnlen(s, len) + 1;
	res = (char *)malloc(sizeof(char) * alloc_size);
	if (res == NULL)
		return (NULL);
	strlcpy(res, s, alloc_size);
	return (res);
}

size_t	find_num_of_sub_str(char *str, char delim)
{
	size_t	num_of_sub_str;

	num_of_sub_str = 1;
	while (*str)
	{
		if (*str++ == delim)
			num_of_sub_str++;
	}
	return (num_of_sub_str);
}

char	**internal_split_free(char **arr, size_t cur)
{
	size_t	i;

	i = 0;
	while (i < cur)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	*find_next_delim(char *str, char delim)
{
	char	*p_delim;

	p_delim = strchr(str, delim);
	if (p_delim == NULL)
		p_delim = strchr(str, '\0');
	return (p_delim);
}

char	**split_main(char *str, char delim, size_t num_of_sub_str)
{
	char	**arr;
	char	*p_delim;
	size_t	i;

	arr = (char **)malloc(sizeof(char *) * (num_of_sub_str + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < num_of_sub_str)
	{
		p_delim = find_next_delim(str, delim);
		arr[i] = ft_strndup(str, p_delim - str);
		if (arr[i] == NULL)
			return (internal_split_free(arr, i));
		str = p_delim + 1;
		i++;
	}
	arr[num_of_sub_str] = NULL;
	return (arr);
}

char	**split_str(char *str, char delim)
{
	char	**res;
	size_t	num_of_sub_str;

	if (str == NULL)
		return (NULL);
	num_of_sub_str = find_num_of_sub_str(str, delim);
	res = split_main(str, delim, num_of_sub_str);
	return (res);
}

void	split_print(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		printf("%s\n", split[i]);
		i++;
	}
	free(split);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exit(EXIT_FAILURE);
	char	**res = split_str(argv[1], ':');
	if (res != NULL)
		split_print(res);
	exit(EXIT_SUCCESS);
}
