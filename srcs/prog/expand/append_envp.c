#include "minishell.h"

int append_envp(t_minishell *shell, char *new_entry)
{
    int count;
    int i;
    char **new_envp; // new array to replace

    count = 0;
    while (shell->envp && shell->envp[count])
        count++; // for new size
    new_envp = malloc(sizeof(char *) * (count + 2)); // new element and NULL
    if (!new_envp)
    {
        free(new_entry);
        return (0);
    }
    i = 0;
    while (i < count)
    {
        new_envp[i] = shell->envp[i];
        i++;
    }
    new_envp[count] = new_entry;
    new_envp[count + 1] = NULL;
    free(shell->envp);
    shell->envp = new_envp; // replace after free
    return (1);
}
