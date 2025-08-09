#include "minishell.h"

int update_existing_env_var(t_minishell *shell, char *name, char *value)
{
    t_env *current = shell->env;

    while (current)
    {
        if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
        {
            free(current->value); // free old value
            current->value = ft_strdup(value); // new value
            update_envp_array(shell, name, value); // update in array
            return (1); // Found and updated
        }
        current = current->next; // until the end of the list
    }
    return (0); // Not found
}