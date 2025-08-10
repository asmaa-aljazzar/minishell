#include "minishell.h"

int create_new_env_var(t_minishell *shell, char *name, char *value)
{
    t_env *current;
    t_env *new_var;

    new_var = malloc(sizeof(t_env));
    if (!new_var)
    {
        ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
        return (0);
    }
    new_var->name = ft_strdup(name);
    if (!new_var->name)
        return (0);
    new_var->value = ft_strdup(value);
    if (!new_var->value)
    {
        free (new_var->name);
        return (0);
    }
    new_var->next = NULL;
    // new node created
    if (!shell->env)// if no var 
        shell->env = new_var; // the new is the first one
    else
    {
        current = shell->env; // first node
        while (current->next) // go until last one
            current = current->next;
        current->next = new_var; // the last point to new one 
    }
    if (!update_envp_array(shell, name, value))
        return (0);
    return (1);
}
