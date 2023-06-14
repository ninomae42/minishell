#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct s_redirect	t_redirect;
struct s_redirect
{
	bool	need_backup_in;
	int		default_in_fd;
	bool	need_backup_out;
	int		default_out_fd;
};

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	size_t		argc;
	char		**argv;
	char		**environ;
	char		*exec_path;
	t_redirect	redirect;
};

// exec_cmd.c
t_cmd	*new_cmd(void);
void	cmd_destroy(t_cmd *cmd);

// exec_main.c
int		exec_cmd(t_ast *ast);

// exec_args.c
size_t	count_argc(t_ast_node *node);
char	**dup_argv(t_ast_node *node, size_t argc);

// exec_path.c
char	*cmd_get_binary_path(char *filename);;

#endif
