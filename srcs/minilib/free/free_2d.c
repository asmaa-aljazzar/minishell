
#include "minishell.h"

void free_2d(char **arr)
{
    int i;

    if (!arr)
        return;
    i = 0;
    while (arr[i])
    {
        free(arr[i]);  // <-- only free if you own these strings separately!
        arr[i] = NULL;
        i++;
    }
    free(arr);
}