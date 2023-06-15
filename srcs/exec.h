#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <fcntl.h>
# include <unistd.h>

# define REDIRECT_IN 1
# define REDIRECT_IN_HDOC 2
# define REDIRECT_OUT 3
# define REDIRECT_OUT_APPEND 4

# define REDIRECT_FILE_MODE 0644

typedef struct s_redirect_node	t_redirect_node;
struct s_redirect_node
{
	int				file_fd;
	int				redirect_type;
	t_redirect_node	*next;
};

typedef struct s_redirect		t_redirect;
struct s_redirect
{
	t_redirect_node	*head;
	t_redirect_node	*tail;
	bool			need_dup_input;
	int				default_in_fd;
	bool			need_dup_output;
	int				default_out_fd;
};

typedef struct s_cmd_node		t_cmd_node;
struct s_cmd_node
{
	t_ast_node	*node;
	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	t_redirect	*redirect;
	t_cmd_node	*next;
};

int				exec_cmd(t_ast *ast);

t_cmd_node		*new_cmd_node(t_ast_node *node);
void			destroy_cmd_node(t_cmd_node *cmd);

// exec_redirect_node.c
t_redirect_node	*new_redirect_node(char *filename, int redirect_type);
void			delete_redirect_node(t_redirect_node *node);

// exec_redirect_set.c
int				r_set_redirect(t_redirect *redirect, t_ast_node *node);

// exec_redirects.c
t_redirect		*new_redirect(void);
void			destroy_redirect(t_redirect *redirect);

// exec_redirect_bakup.c
int				r_backup_out_fd(t_redirect *redirect);
void			r_reset_out_redirect(t_redirect *redirect);
int				r_backup_in_fd(t_redirect *redirect);
void			r_reset_in_redirect(t_redirect *redirect);


// exec_redirect_out.c
int				set_output_redirect(t_ast_node *node, t_redirect *redirect);
int				do_input_redirect(char *filename, t_redirect *redirect);

// exec_arguments.c
size_t			count_argc(t_ast_node *node);
char			**alloc_argv(size_t argc);
void			set_argv(char **argv, t_ast_node *node);

// exec_path.c
char			*cmd_get_binary_path(char *filename);;

#endif
