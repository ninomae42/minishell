#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <sys/wait.h>

typedef struct s_cmd_node	t_cmd_node;
struct s_cmd_node{
	char		*filename;
	size_t		argc;
	char		**argv;
	char		**environ;
	t_cmd_node	*next;
};

int	exec_command(t_node *ast);

#endif
