#ifndef ENVIRON_H
# define ENVIRON_H
#include "libft.h"
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_env_node	t_env_node;
struct s_env_node{
	char		*name;
	char		*value;
	char		*str;
	t_env_node	*next;
};

typedef struct s_env	t_env;
struct s_env{
	t_env_node	*head;
	t_env_node	*tail;
	size_t		size;
};

// env_init.c
t_env		*env_new(void);
t_env_node	*env_new_node(t_env_node *current, char *name, char *value, char *str);
void		env_free_all_node(t_env_node *head);
void		env_dealloc(t_env *env);

// env_entry.c
char		*env_entry_new_str(const char *name, const char *value);
void		env_entry_print(t_env *env);
size_t		env_entry_size(t_env *env);
char		**env_entry_alloc_environ(t_env *env);

// load_env.c
int			load_env(t_env *env, char **environ);

// ft_getenv.c
char		*ft_getenv(t_env *env, const char *name);

// ft_setenv.c
int			ft_setenv(t_env *env, const char *name, const char *value, int overwrite);

// ft_unsetenv.c
int			ft_unsetenv(t_env *env, const char *name);

// ft_printenv.c
void		ft_printenv(t_env *env);

// env_utils.c
t_env_node	*env_find_node(t_env *env, const char *name);
bool		is_env_name_valid(const char *name);
size_t		env_entry_len(t_env *env);

#endif
