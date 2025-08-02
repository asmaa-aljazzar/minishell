
#include "minishell.h"

char *expand_variable(t_minishell *minishell, char *token)
{
    size_t i;
    char *result;
    char *temp;

    i = 0;
    result = ft_strdup("");
    if (!result || !token)
        return NULL;
    while (token[i])
    {
        if (token[i] == '$')
            handle_dollar(minishell, token, &i, &result);
        else
        {
            temp = extract_literal(token, &i);
            append_and_free(&result, temp);
        }
    }
    return result;
}
