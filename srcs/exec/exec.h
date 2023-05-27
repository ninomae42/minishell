#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include "environ.h"
# include "utils.h"
# include <sys/wait.h>

typedef struct s_cmd_node	t_cmd_node;
struct s_cmd_node{
	char		*filename;
	size_t		argc;
	char		**argv;
	char		**environ;
	t_cmd_node	*next;
};

// exec.c
int		exec_command(t_node *ast, t_env *env);

// find_executable_path.c
char	*find_executable_path(char *filename, t_env *env);

#endif
