#include "minishell.h"

void free_split_array(char **array)
{
    if (!array)
        return;
    int i = 0;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    free(array);
}