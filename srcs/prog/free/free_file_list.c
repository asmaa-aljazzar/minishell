
#include "minishell.h"

void free_file_list(char **list)
{
    if (!list)
        return;
    int i;
    i = 0;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
    free(list);
}
