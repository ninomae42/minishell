#ifndef EXEC_H
# define EXEC_H
# include "parser.h"

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	size_t	argc;
	char	**argv;
	char	**environ;
	char	*exec_path;
};

// exec_cmd.c
t_cmd	*new_cmd(void);
void	cmd_destroy(t_cmd *cmd);

#endif
