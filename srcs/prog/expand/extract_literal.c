
#include "minishell.h"

char	*extract_literal(char *token, size_t *i)
{
	size_t	start;

	start = *i;
	while (token[*i] && token[*i] != '$')
		(*i)++;
	return (ft_substr(token, start, *i - start)); //todo norm error
}
