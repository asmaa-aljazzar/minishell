#include "minishell.h"

void	handle_dollar(t_minishell *ms, char *token, size_t *i, char **result)
{
	char	*value;
	int		should_free;

	value = NULL;
	should_free = 0;
	(*i)++;
	if (token[*i] == '?')
	{
		value = ft_itoa(ms->exit_code);
		should_free = 1;
		(*i)++;
	}
	if (token[*i] == '0')
	{
		value = "./minishell";
		(*i)++;
	}
	else if (ft_isdigit(token[*i]))
	{
		(*i)++;
		return ;
	}
	else
		value = extract_var_value(ms, token, i);
	*result = append_result(*result, value);
	if (should_free)
		free(value);
}
