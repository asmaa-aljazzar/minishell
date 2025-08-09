#include "minishell.h"

char *build_envp_entry(char *name, char *value)
{
    char *temp = ft_strjoin(name, "=");
    char *entry = ft_strjoin(temp, value);
    free(temp);
    return (entry);
}