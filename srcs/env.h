/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tashimiz <tashimiz@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 10:01:18 by tashimiz          #+#    #+#             */
/*   Updated: 2023/06/29 10:01:18 by tashimiz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	size_t			size;
	t_env_node		*head;
	t_env_node		*tail;
	int				status;
	volatile int	signo;
	bool			is_readline_interrupted;
};

// env_main.c
t_env		*new_env(void);
void		destroy_env(t_env *env);
t_env_node	*new_env_node(char *name, char *value, char *pait_str);
void		destroy_env_node(t_env_node *node);
void		destroy_env_nodes(t_env_node *head);

// env_utils.c
bool		env_is_name_valid(char *name);
t_env_node	*env_find_node(t_env *env, char *name);
char		*make_pair_str(char *name, char *value);
char		**env_list_to_environ(t_env *env);

// env_add.c
int			env_set(t_env *env, char *name, char *value, int overwrite);

// env_delete.c
int			env_unset(t_env *env, char *name);

// env_get.c
char		*env_get_value(t_env *env, char *name);
char		*env_get_pair_str(t_env *env, char *name);

// env_load_environ.c
int			env_load_environ(t_env *env, char **environ);

int			ft_strcmp(const char *s1, const char *s2);

#endif
