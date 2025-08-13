#include "minishell.h"

char *append_to_result(char *result, char *to_append)
{
    char *temp;
    
    temp = result;
    result = ft_strjoin(result, to_append);
    free(temp);
    return (result);
}
