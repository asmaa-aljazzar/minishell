#include "minishell.h"

char *build_envp_entry(char *name, char *value)
{
    char *temp = ft_strjoin(name, "=");
    if (!temp)
        return (NULL);
    char *entry = ft_strjoin(temp, value);
    free(temp);
    if (!entry)
        return (NULL);
    return (entry);
}
