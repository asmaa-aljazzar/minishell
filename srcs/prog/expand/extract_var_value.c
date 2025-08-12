
#include "minishell.h"

char	*extract_var_value(t_minishell *ms, char *token, size_t *i)
{
	size_t	start;
	char	*var_name;
	char	*value;

	start = *i;
	while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
		(*i)++;
	var_name = ft_substr(token, start, *i - start);
	value = get_env_value(ms->env, var_name);
	free(var_name);
	return (value);
}
