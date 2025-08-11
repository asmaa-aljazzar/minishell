#include "minishell.h"

char	*handle_empty_expansion(char *token)
{
	if (!token)
		return (ft_strdup(""));

	if (ft_strcmp(token, "$") == 0)
		return (ft_strdup("$"));

	if (token[0] == '\0')
		return (ft_strdup(""));

	return (NULL); // Not an empty expansion case
}