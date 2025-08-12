#include "minishell.h"

char *extract_var_name(char *str, int *index)
{
    char var_name[256];
    char *res;
    int j = 0;
    
    while (str[*index] && (ft_isalnum(str[*index]) || str[*index] == '_'))
    {
        var_name[j++] = str[*index];
        (*index)++;
    }
    var_name[j] = '\0';
    res = ft_strdup (var_name);
    return (res);
}