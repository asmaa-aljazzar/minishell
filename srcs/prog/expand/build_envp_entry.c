#include "minishell.h"

char	*build_envp_entry(char *name, char *value)
{
	char	*temp;
	char	*entry;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	if (!entry)
		return (NULL);
	return (entry);
}
