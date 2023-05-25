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
	t_env_node	*next;
};

typedef struct s_env	t_env;
struct s_env{
	t_env_node	*head;
	t_env_node	*tail;
};

// env_init.c
t_env		*env_new(void);
t_env_node	*env_new_node(t_env_node *current, char *name, char *value);
void		env_free_all_node(t_env_node *head);
void		env_dealloc(t_env *env);

#endif
