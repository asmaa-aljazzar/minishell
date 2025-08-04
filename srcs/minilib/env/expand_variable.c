
#include "minishell.h"

char *handle_empty_expansion(char *token)
{
    if (!token)
        return ft_strdup("");

    if (ft_strcmp(token, "$") == 0)
        return ft_strdup("$");

    if (token[0] == '\0')
        return ft_strdup("");

    return NULL; // Not an empty expansion case
}
char *expand_variable(t_minishell *minishell, char *token)
{
    size_t i;
    char *result;
    char *temp;
    char *empty_check = handle_empty_expansion(token);
    if (empty_check)
        return empty_check;
    if (ft_strcmp(token, "$") == 0)
        return ft_strdup("$");
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
