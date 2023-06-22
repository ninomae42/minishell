#ifndef ENV_H
# define ENV_H
# include <stdbool.h>
# include <stdlib.h>
# include "ft_err.h"
# include "libft.h"

typedef struct s_env_node	t_env_node;
struct s_env_node
{
	char		*name;
	char		*value;
	char		*pair_str;
	t_env_node	*next;
};

typedef struct s_env		t_env;
struct s_env
{
	size_t		size;
	t_env_node	*head;
	t_env_node	*tail;
};

// env_main.c
t_env		*new_env(void);
void		destroy_env(t_env *env);
t_env_node	*new_env_node(char *name, char *value);
void		destroy_env_node(t_env_node *node);
void		destroy_env_nodes(t_env_node *head);

// env_utils.c
bool		env_is_name_valid(char *name);
t_env_node	*env_find_node(t_env *env, char *name);
char		*make_pair_str(char *name, char *value);
void		env_print(t_env *env);

#endif
