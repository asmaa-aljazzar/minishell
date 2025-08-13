#include "minishell.h"

int	update_env_var(t_minishell *shell, char *name, char *value)
{
	if (!name || !value)
		return (0);
	if (!update_existing_env_var(shell, name, value))//todo
	{
		if (!create_new_env_var(shell, name, value))//todo
			return (0);
	}
	else if (update_existing_env_var(shell, name, value) == -1)//todo
		return (0);
	return (1);
}
