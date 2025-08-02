
#include "minishell.h"

void append_and_free(char **result, char *to_add)
{
    char *temp = *result;
    *result = ft_strjoin(*result, to_add);
    free(temp);
    free(to_add);
}