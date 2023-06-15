#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct s_cmd_node	t_cmd_node;
struct s_cmd_node
{
	t_ast_node	*node;
	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	t_cmd_node	*next;
};

int	exec_cmd(t_ast *ast);

t_cmd_node	*new_cmd_node(t_ast_node *node);
void		destroy_cmd_node(t_cmd_node *cmd);

// exec_path.c
char	*cmd_get_binary_path(char *filename);;

#endif
