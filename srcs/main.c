#include "minishell.h"
#include "tokenizer.h"

extern char	**environ;

char	**token2argv(t_token *token)
{
	char			**argv;
	t_token_node	*node;
	size_t			i;

	argv = (char **)malloc(sizeof(char *) * (token->size));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node = token->head;
	i = 0;
	while (node != NULL && node->kind != TK_EOF)
	{
		argv[i] = node->literal;
		node = node->next;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

void	print_cmds(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
}


int	exec(t_token *token)
{
	char	*filename;
	char	**argv;
	pid_t	pid;
	int		status;

	status = 0;
	if (token->size == 1)
		return (status);
	argv = token2argv(token);
	// print_cmds(argv);
	filename = argv[0];
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(filename, (char *const *)argv, environ) < 0)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
		free(argv);
		return (status);
	}
	return (status);
}

int	main(void)
{
	int		status;
	char	*line;

	rl_outstream = stderr;
	status = 0;
	while (true)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (*line == '\0')
		{
			free(line);
			continue;
		}
		t_token *token = tokenize(line);
		// token_print(token);
		status = exec(token);
		token_destroy(token);
		free(line);
	}
	exit(status);
}
