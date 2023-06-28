#include "builtin.h"

static void	print_env_node(t_env_node *node)
{
	if (node->value == NULL)
		return ;
	ft_putstr_fd(node->name, STDOUT_FILENO);
	ft_putchar_fd('=', STDOUT_FILENO);
	ft_putendl_fd(node->value, STDOUT_FILENO);
}

int	builtin_env(char **argv)
{
	t_env_node	*head;

	(void)argv;
	head = g_env->head;
	while (head)
	{
		print_env_node(head);
		head = head->next;
	}
	return (EXIT_SUCCESS);
}
