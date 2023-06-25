#include "exec.h"

void	destroy_redirect_nodes(t_redirect_node *head)
{
	t_redirect_node	*next;

	while (head)
	{
		next = head;
		free(head->filename);
		free(head);
		head = next;
	}
}

void	destroy_redirect(t_redirect *redirect)
{
	if (redirect == NULL)
		return ;
	destroy_redirect_nodes(redirect->head);
	free(redirect);
}

void	destroy_cmd_node(t_cmd_node *node)
{
	if (node == NULL)
		return ;
	destroy_redirect(node->redirects);
	free(node->argv);
	free(node->environ);
	free(node->binary_path);
	free(node);
}

void	destroy_cmd_nodes(t_cmd_node *head)
{
	t_cmd_node	*next;

	while (head)
	{
		next = head->next;
		destroy_cmd_node(head);
		head = next;
	}
}

void	destroy_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return ;
	free(cmd);
}
