#ifndef EXEC_H
# define EXEC_H
# include "parser.h"
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>

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
	pid_t		pid;
	int			pipe_mode;
	int			pipe_read_fd;
	int			pipe_write_fd;
	t_ast_node	*node;
	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	t_redirect	*redirect;
	t_cmd_node	*next;
};

typedef struct s_cmd			t_cmd;
struct s_cmd
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	size_t		num_of_commands;
};

int				exec_cmd(t_ast *ast);
void			exec_simple_command_child(t_cmd_node *cmd);

t_cmd_node		*new_cmd_node(t_ast_node *node);
void			destroy_cmd_node(t_cmd_node *cmd);
void			destroy_cmd(t_cmd *cmd);

// exec_pipeline.c
int				exec_pipeline(t_cmd *cmd);

// exec_pipeline_fork.c
int				exec_fork_procs(t_cmd_node *current, t_cmd_node *prev);

// exec_pipeline_wait.c
void			exec_terminate_procs(t_cmd_node *current);
int				exec_wait_procs(t_cmd *commands);

// exec_redirect_node.c
t_redirect_node	*new_redirect_node(char *filename, int redirect_type);
void			delete_redirect_node(t_redirect_node *node);

// exec_redirect_set.c
int				r_set_redirect(t_redirect *redirect, t_ast_node *node);
bool			exec_node_is_redirect(t_ast_node *node);

// exec_redirects.c
t_redirect		*new_redirect(void);
void			destroy_redirect(t_redirect *redirect);

// exec_redirect_bakup.c
int				r_backup_out_fd(t_redirect *redirect);
void			r_reset_out_redirect(t_redirect *redirect);
int				r_backup_in_fd(t_redirect *redirect);
void			r_reset_in_redirect(t_redirect *redirect);

// exec_redirect_out.c
int				r_do_redirect(t_redirect *redirect);

// exec_arguments.c
size_t			count_argc(t_ast_node *node);
char			**alloc_argv(size_t argc);
void			set_argv(char **argv, t_ast_node *node);

// exec_path.c
char			*cmd_get_binary_path(char *filename);;

// exec_syscall.c
int				ft_fork(void);
int				ft_pipe(int filedes[2]);
int				ft_kill(pid_t pid, int sig);

#endif
