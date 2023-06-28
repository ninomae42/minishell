#ifndef EXEC_H
# define EXEC_H
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "minishell.h"
# include "builtin.h"
# include "ft_err.h"
# include "ft_path.h"
# include "env.h"
# include "parser.h"
# include "libft.h"

# define FILE_MODE 0644

typedef struct s_cmd_node		t_cmd_node;
typedef struct s_cmd			t_cmd;
typedef struct s_redirect_node	t_redirect_node;
typedef struct s_redirect		t_redirect;

typedef enum e_pipe_mode
{
	PIPE_NONE,
	PIPE_RD,
	PIPE_WR,
	PIPE_RDWR,
}	t_pipe_mode;

struct s_cmd
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	size_t		num_of_commands;
};

struct s_cmd_node
{
	t_ast_node	*node;

	size_t		argc;
	char		**argv;
	char		**environ;
	char		*binary_path;
	bool		is_builtin;

	pid_t		pid;

	t_pipe_mode	pipe_mode;
	int			pipe_fd_read;
	int			pipe_fd_write;

	t_redirect	*redirects;
	t_cmd_node	*next;
};

typedef enum e_redirect_type
{
	RDIR_IN,
	RDIR_HDOC,
	RDIR_OUT,
	RDIR_APPEND,
}	t_redir_type;

struct s_redirect
{
	t_redirect_node	*head;
	t_redirect_node	*tail;
	bool			need_dup_input;
	int				fd_in_dup;
	bool			need_dup_output;
	int				fd_out_dup;
};

struct s_redirect_node
{
	t_redir_type	type;
	int				fd;
	char			*filename;
	t_redirect_node	*next;
};

// exec_main.c
void			execute_command(t_cmd *cmd);

// exec_binary.c
void			exec(char *command_name, char **argv, char **environ);

// exec_parent.c
int				execute_builtin_in_parent(t_cmd_node *command);

// exec_cmd.c
t_cmd			*new_cmd(void);
t_cmd_node		*new_cmd_node(t_ast_node *node);

// exec_dealloc.c
void			destroy_redirect_nodes(t_redirect_node *head);
void			destroy_redirect(t_redirect *redirect);
void			destroy_cmd_node(t_cmd_node *node);
void			destroy_cmd_nodes(t_cmd_node *head);
void			destroy_cmd(t_cmd *cmd);

// exec_build.c
t_cmd			*build_command(t_ast *ast);

// exec_redirect.c
t_redirect		*new_redirect(void);
t_redirect_node	*new_redirect_node(t_redir_type type);
void			reset_redirect(t_redirect *redirect);

// exec_redirect_prepare.c
void			prepare_redirect(t_cmd_node *command);

// exec_redirect_set.c
int				setup_redirects(t_redirect *redirects);

// exec_pipes.c
void			set_pipe_state(t_cmd_node *current, t_cmd_node *prev);
void			open_pipe(t_cmd_node *command);
void			close_pipe(t_cmd_node *command);
void			connect_pipes(t_cmd_node *current, t_cmd_node *prev);

// exec_heredoc.c
int				read_heredoc(char *delimiter);

#endif
