#include "builtin.h"
#include "expander.h"

void	print_env_node(t_env_node *node)
{
	char	*escaped_value;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(node->name, STDOUT_FILENO);
	if (node->value)
	{
		escaped_value = get_escaped_str(node->value);
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(escaped_value, STDOUT_FILENO);
		ft_putchar_fd('"', STDOUT_FILENO);
		free(escaped_value);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	export_print(void)
{
	t_env_node	*node;
	t_env_node	*next;

	// TODO: sort environment node list
	node = g_env->head;
	while (node)
	{
		next = node->next;
		print_env_node(node);
		node = next;
	}
	return (EXIT_SUCCESS);
}
