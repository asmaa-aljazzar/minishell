
#include "minishell.h"

char *expand_variable(t_minishell *ms, char *token)
{
    size_t i;
    char *result;
    char *temp;
    char *empty_check;

    if (!token)
        return ft_strdup("");
    empty_check = handle_empty_expansion(token);
    if (empty_check)
        return empty_check;
    result = ft_strdup("");
    if (!result)
        return NULL;
    i = 0;
    while (token[i])
    {
        if (token[i] == '$')
            handle_dollar(ms, token, &i, &result);
        else
        {
            temp = extract_literal(token, &i);
            append_and_free(&result, temp);
        }
    }
    return result;
}
