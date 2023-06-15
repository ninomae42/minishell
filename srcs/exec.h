#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <fcntl.h>
# include <unistd.h>

typedef struct s_redirect	t_redirect;
struct s_redirect
{
	bool	need_dup_input;
	int		default_in_fd;
	bool	need_dup_output;
	int		default_out_fd;
};

typedef struct s_cmd_node	t_cmd_node;
struct s_cmd_node
{
	t_ast_node	*node;
	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	t_redirect	redirect;
	t_cmd_node	*next;
};

int	exec_cmd(t_ast *ast);

t_cmd_node	*new_cmd_node(t_ast_node *node);
void		destroy_cmd_node(t_cmd_node *cmd);

// exec_redirects.c
void		init_redirect(t_redirect *redirect);
int			backup_output_fd(t_redirect *redirect);
void		reset_output_redirect(t_redirect *redirect);
int			backup_input_fd(t_redirect *redirect);
void		reset_input_redirect(t_redirect *redirect);

// exec_redirect_out.c
int			set_output_redirect(t_ast_node *node, t_redirect *redirect);
int			do_input_redirect(char *filename, t_redirect *redirect);

// exec_arguments.c
size_t		count_argc(t_ast_node *node);
char		**alloc_argv(size_t argc);
void		set_argv(char **argv, t_ast_node *node);

// exec_path.c
char	*cmd_get_binary_path(char *filename);;

#endif
