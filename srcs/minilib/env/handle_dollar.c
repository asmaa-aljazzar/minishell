
#include "minishell.h"


void handle_dollar(t_minishell *minishell, char *token, size_t *i, char **result)
{
    char *value = NULL;
    int should_free = 0;

    (*i)++;
    if (token[*i] == '?')
    {
        value = ft_itoa(minishell->exit_code);
        should_free = 1;
        (*i)++;
    }
    else
        value = extract_var_value(minishell, token, i);

    *result = append_result(*result, value);

    if (should_free)
        free(value);
}
