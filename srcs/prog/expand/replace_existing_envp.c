#include "minishell.h"

int	replace_existing_envp(t_minishell *shell, char *name, char *new_entry)
{
	int	i;

	i = 0;
	while (shell->envp && shell->envp[i]) // loop over elements in array
	{
		// compare between name and name in array and after name length there is a '='
		if (ft_strncmp(shell->envp[i], name, ft_strlen(name)) == 0
			&& shell->envp[i][ft_strlen(name)] == '=')
		{
			free(shell->envp[i]); // free old value
			shell->envp[i] = new_entry;
			return (1); // Replaced
		}
		i++;
	}
	return (0); // Not found
}
