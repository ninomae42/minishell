#include "exec.h"

static int	open_redirect_file(char *filename, int redirect_type)
{
	int	fd;

	if (redirect_type == REDIRECT_IN)
		fd = open(filename, O_RDONLY);
	else if (redirect_type == REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, REDIRECT_FILE_MODE);
	else if (redirect_type == REDIRECT_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, REDIRECT_FILE_MODE);
	else
		fd = -1;
	if (fd < 0)
	{
		err_perror(errno);
		return (-1);
	}
	return (fd);
}

t_redirect_node	*new_redirect_node(char *filename, int redirect_type)
{
	int				file_fd;
	t_redirect_node	*node;

	file_fd = open_redirect_file(filename, redirect_type);
	if (file_fd < 0)
		return (NULL);
	node = (t_redirect_node *)malloc(sizeof(t_redirect_node));
	if (node == NULL)
		ft_fatal("malloc");
	node->file_fd = file_fd;
	node->next = NULL;
	return (node);
}

void	delete_redirect_node(t_redirect_node *node)
{
	t_redirect_node	*next;

	while (node != NULL)
	{
		next = node->next;
		close(node->file_fd);
		free(node);
		node = next;
	}
}

int	r_add_redirect_node(t_redirect *redirect, char *filename, int redirect_type)
{
	t_redirect_node	*node;

	node = new_redirect_node(filename, redirect_type);
	if (node == NULL)
		return (-1);
	if (redirect->head == NULL)
		redirect->head = node;
	else
		redirect->tail->next = node;
	redirect->tail = node;
	return (0);
}

int	r_set_redirect(t_redirect *redirect, t_ast_node *node)
{
	char	*filename;
	int		res;

	filename = node->child->literal;
	res = 0;
	if (node->kind == ND_REDIRECT_IN)
		res = r_add_redirect_node(redirect, filename, REDIRECT_IN);
	else if (node->kind == ND_REDIRECT_OUT)
		res = r_add_redirect_node(redirect, filename, REDIRECT_OUT);
	else if (node->kind == ND_REDIRECT_OUT_APPEND)
		res = r_add_redirect_node(redirect, filename, REDIRECT_OUT_APPEND);
	else
		;
	if (res < 0)
		return (-1);
	return (0);
}
