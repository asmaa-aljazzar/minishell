
#include "minishell.h"

static int is_valid_identifier(const char *str);
static void remove_from_env_list(t_minishell *shell, const char *name);
static void remove_from_envp_array(t_minishell *shell, const char *name);

void unset_builtin(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    int i = 1;
    
    shell->exit_code = 0;
    
    // No arguments is not an error in unset
    if (!cmd->argv[1])
        return;
    
    // Process each argument
    while (cmd->argv[i])
    {
        // Validate identifier
        if (!is_valid_identifier(cmd->argv[i]))
        {
            ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
            ft_putstr_fd(cmd->argv[i], STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            shell->exit_code = 1;
        }
        else
        {
            // Remove from both env list and envp array
            remove_from_env_list(shell, cmd->argv[i]);
            remove_from_envp_array(shell, cmd->argv[i]);
        }
        i++;
    }
}

static void remove_from_env_list(t_minishell *shell, const char *name)
{
    t_env *current = shell->env;
    t_env *prev = NULL;
    
    while (current)
    {
        if (ft_strcmp(current->name, name) == 0)
        {
            // Found the variable to remove
            if (prev)
                prev->next = current->next;
            else
                shell->env = current->next;
            
            // Free the node
            free(current->name);
            if (current->value)
                free(current->value);
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

static void remove_from_envp_array(t_minishell *shell, const char *name)
{
    char **new_envp;
    int count = 0;
    int i, j;
    int name_len = ft_strlen(name);
    
    if (!shell->envp)
        return;
    
    // Count current entries
    while (shell->envp[count])
        count++;
    
    if (count == 0)
        return;
    
    // Create new array (might be same size if variable not found)
    new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return;
    
    // Copy entries except the one to remove
    i = 0;
    j = 0;
    while (i < count)
    {
        // Check if this entry matches the variable to remove
        if (ft_strncmp(shell->envp[i], name, name_len) == 0 && 
            shell->envp[i][name_len] == '=')
        {
            // This is the variable to remove, skip it
            free(shell->envp[i]);
        }
        else
        {
            // Keep this variable
            new_envp[j] = shell->envp[i];
            j++;
        }
        i++;
    }
    
    new_envp[j] = NULL;
    
    // Replace old array
    free(shell->envp);
    shell->envp = new_envp;
}

static int is_valid_identifier(const char *str)
{
    int i = 0;
    
    if (!str || str[0] == '\0')
        return 0;
    
    // First character must be letter or underscore
    if (!ft_isalpha(str[0]) && str[0] != '_')
        return 0;
    
    // Rest must be alphanumeric or underscore
    i = 1;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return 0;
        i++;
    }
    
    return 1;
}