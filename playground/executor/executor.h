#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>

# define REDIRECT_IN 1
# define REDIRECT_IN_HDOC 2
# define REDIRECT_OUT 3
# define REDIRECT_OUT_APPEND 4

# define REDIRECT_FILE_MODE 0644

# define ND_WORD 1
# define ND_REDIECT_IN 2
# define ND_REDIECT_IN_HDOC 3
# define ND_REDIECT_OUT 4
# define ND_REDIECT_OUT_APPEND 5

# define PIPE_READ 0
# define PIPE_WRITE 1
# define PIPE_READ_WRITE 2
# define PIPE_NO_PIPE 3


typedef struct t_env			t_env;
char	**env_list_to_environ(t_env *env);

typedef struct s_ast			t_ast;
typedef struct s_ast_node		t_ast_node;
typedef struct s_ast
{
	t_ast_node	*root;
}	t_ast;

typedef struct s_ast_node
{
	int			kind;
	t_ast_node	*brother;
	t_ast_node	*child;
	char		*literal;
}	t_ast_node;

typedef struct s_redirect_node	t_redirect_node;
typedef struct s_redirect		t_redirect;
typedef struct s_cmd_node		t_cmd_node;
typedef struct s_cmd			t_cmd;

typedef struct s_redirect
{
	t_redirect_node	*head;
	t_redirect_node	*tail;
	bool			need_dup_input;
	int				stash_in_fd;
	bool			need_dup_output;
	int				stash_out_fd;
}	t_redirect;

typedef struct s_redirect_node
{
	int				redirect_type;
	int				fd;
	char			*filename;
	t_redirect_node	*next;
}	t_redirect_node;

typedef struct s_cmd
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	size_t		num_of_commands;
}	t_cmd;

typedef struct s_cmd_node
{
	t_ast_node	*node;

	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	bool		is_builtin;

	pid_t		pid;

	int			pipe_mode;
	int			pipe_fd_read;
	int			pipe_fd_write;

	t_redirect	*redirects;
	t_cmd_node	*next;
}	t_cmd_node;

t_cmd		*new_cmd(void);
t_cmd_node	*new_cmd_node(t_ast_node *node);

void	prepare_redirect(t_cmd_node *command);

// exec_build_cmd.c
t_cmd	*build_command(t_ast *ast, t_env *env);

int	execute_builtin_in_parent(t_cmd_node *command);
int	execute_builtin(char **argv);

// exec_pipe.c
void	set_pipe_state(t_cmd_node *current, t_cmd_node *prev);
void	open_pipe(t_cmd_node *command);
void	close_pipe(t_cmd_node *command);
void	connect_pipes(t_cmd_node *current, t_cmd_node *prev);


#endif
