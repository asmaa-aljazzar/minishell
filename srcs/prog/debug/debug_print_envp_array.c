#include "minishell.h"

void debug_print_envp_array(char **envp)
{
    int i = 0;

    if (!envp)
    {
        printf("[debug] Environment array is NULL.\n");
        return;
    }

    printf("[debug] Environment array contents:\n");
    while (envp[i])
    {
        printf("  [%d] \"%s\"\n", i, envp[i]);
        i++;
    }
}
