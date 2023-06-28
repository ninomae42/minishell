#include "expander.h"

static char	*expand_parameter_internal(char **word)
{
	char	*i_word;
	char	*save_word;
	char	*name;
	char	*value;

	i_word = *word;
	save_word = i_word;
	// validate identifier or not ?
	while (*i_word && is_alpha_num_under(*i_word))
		i_word++;
	*word = i_word;
	name = ft_strndup(save_word, i_word - save_word);
	if (name == NULL)
		err_fatal(errno);
	value = env_get_value(g_env, name);
	free(name);
	if (value == NULL)
		return (NULL);
	value = get_escaped_str(value);
	if (value == NULL)
		err_fatal(errno);
	return (value);
}

char	*expand_parameter(char **word)
{
	char	*i_word;
	char	*value;

	i_word = *word;
	i_word++;
	if (*i_word == '?')
	{
		value = ft_itoa(g_env->status);
		i_word++;
	}
	else
		value = expand_parameter_internal(&i_word);
	*word = i_word;
	return (value);
}
