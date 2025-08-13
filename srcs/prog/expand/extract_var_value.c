
#include "minishell.h"

char	*extract_var_value(t_minishell *ms, char *token, size_t *i)
{
	size_t	start;
	char	*var_name;
	char	*value;

	start = *i;
	if (ft_isdigit(token[*i]))
		(*i)++;
	else
	{
		while (token[*i] && (ft_isalnum(token[*i]) || token[*i] == '_'))
			(*i)++;
	}
	var_name = ft_substr(token, start, *i - start);
	value = get_env_value(ms->env, var_name, ms->mini_file);
	free(var_name);
	return (value);
}
