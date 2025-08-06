// update_env_var.c
#include "minishell.h"

void update_env_var(t_minishell *shell, char *name, char *value)
{
    t_env *current;
    t_env *new_var;
    
    if (!name || !value)
        return;
    
    // Search for existing variable
    current = shell->env;
    while (current)
    {
        if (ft_strncmp(current->name, name, ft_strlen (name)) == 0)
        {
            // Variable exists, update its value
            free(current->value);
            current->value = ft_strdup(value);
            
            // Also update in envp array
            update_envp_array(shell, name, value);
            return;
        }
        current = current->next;
    }
    
    // Variable doesn't exist, create new one
    new_var = malloc(sizeof(t_env));
    if (!new_var)
    {
        ft_putstr_fd("minishell: malloc failed\n", STDERR_FILENO);
        return;
    }
    
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;
    
    // Add to end of list
    if (!shell->env)
    {
        shell->env = new_var;
    }
    else
    {
        current = shell->env;
        while (current->next)
            current = current->next;
        current->next = new_var;
    }
    
    // Update envp array
    update_envp_array(shell, name, value);
}

// update_envp_array.c
#include "minishell.h"

void update_envp_array(t_minishell *shell, char *name, char *value)
{
    char **new_envp;
    char *new_entry;
    int count = 0;
    int i = 0;
    int found = 0;
    
    // Create new entry string "NAME=value"
    new_entry = ft_strjoin(name, "=");
    char *temp = new_entry;
    new_entry = ft_strjoin(temp, value);
    free(temp);
    
    // Count current envp entries
    while (shell->envp && shell->envp[count])
        count++;
    
    // Check if variable already exists
    i = 0;
    while (i < count)
    {
        if (ft_strncmp(shell->envp[i], name, ft_strlen(name)) == 0 &&
            shell->envp[i][ft_strlen(name)] == '=')
        {
            // Replace existing entry
            free(shell->envp[i]);
            shell->envp[i] = new_entry;
            found = 1;
            break;
        }
        i++;
    }
    
    // If not found, add new entry
    if (!found)
    {
        // Allocate new array with one more slot
        new_envp = malloc(sizeof(char *) * (count + 2));
        if (!new_envp)
        {
            free(new_entry);
            return;
        }
        
        // Copy existing entries
        i = 0;
        while (i < count)
        {
            new_envp[i] = shell->envp[i];
            i++;
        }
        
        // Add new entry
        new_envp[count] = new_entry;
        new_envp[count + 1] = NULL;
        
        // Free old array and update pointer
        free(shell->envp);
        shell->envp = new_envp;
    }
}