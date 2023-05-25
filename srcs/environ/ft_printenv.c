#include "environ.h"

void	ft_printenv(t_env *env)
{
	t_env_node	*current;

	if (env == NULL)
		return ;
	current = env->head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->value);
		current = current->next;
	}
}
