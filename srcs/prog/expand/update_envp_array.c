#include "minishell.h"

int	update_envp_array(t_minishell *shell, char *name, char *value)
{
	char	*new_entry;

	if (!name || !value)
		return (0);
	new_entry = build_envp_entry(name, value); // ["NAME=VAL"]
	if (!new_entry)
		return (0);
	if (!replace_existing_envp(shell, name, new_entry))
	{
		if (!append_envp(shell, new_entry))
			return (0);
	}
	return (1);
}
