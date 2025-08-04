#include "minishell.h"

static int is_valid_identifier(const char *str);
static void update_or_add_env(t_minishell *minishell, char *name, char *value);
static void export_without_value(t_minishell *minishell, char *name);

void export_builtin(t_minishell *minishell)
{
    t_command *cmd = minishell->cmd;
    char *equal_position;
    char *name;
    char *value;
    int i;

    // Safety checks
    if (!cmd || !cmd->argv || !cmd->argv[0])
    {
        minishell->exit_code = 1;
        return;
    }

    minishell->exit_code = 0;

    // No arguments - print all exported variables in sorted format
    if (!cmd->argv[1])
    {
        print_sorted_env(minishell);
        return;
    }

    // Process each argument
    i = 1;
    while (cmd->argv[i])
    {
        if (cmd->argv[i])
        {
            equal_position = ft_strchr(cmd->argv[i], '=');
            if (equal_position)
            {
                // Split name and value
                *equal_position = '\0';
                name = cmd->argv[i];
                value = equal_position + 1;
                
                // Validate and update
                if (is_valid_identifier(name))
                {
                    update_or_add_env(minishell, name, value);
                }
                else
                {
                    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
                    ft_putstr_fd(name, STDERR_FILENO);
                    ft_putstr_fd("=", STDERR_FILENO);
                    ft_putstr_fd(value, STDERR_FILENO);
                    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
                    minishell->exit_code = 1;
                }
                
                // Restore original string
                *equal_position = '=';
            }
            else
            {
                // Export without value
                if (is_valid_identifier(cmd->argv[i]))
                {
                    export_without_value(minishell, cmd->argv[i]);
                }
                else
                {
                    ft_putstr_fd("minishell: export: `", STDERR_FILENO);
                    ft_putstr_fd(cmd->argv[i], STDERR_FILENO);
                    ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
                    minishell->exit_code = 1;
                }
            }
        }
        i++;
    }
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

static void update_or_add_env(t_minishell *minishell, char *name, char *value)
{
    t_env *current;
    t_env *new_var;
    
    if (!minishell || !name || !value)
        return;
    
    // Search for existing variable
    current = minishell->env;
    while (current)
    {
        if (current->name && ft_strcmp(current->name, name) == 0)
        {
            // Variable exists, update its value
            if (current->value)
                free(current->value);
            current->value = ft_strdup(value);
            
            // Also update in envp array
            update_envp_array(minishell, name, value);
            return;
        }
        current = current->next;
    }
    
    // Variable doesn't exist, create new one
    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    
    new_var->name = ft_strdup(name);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;
    
    if (!new_var->name || !new_var->value)
    {
        if (new_var->name)
            free(new_var->name);
        if (new_var->value)
            free(new_var->value);
        free(new_var);
        return;
    }
    
    // Add to end of list
    if (!minishell->env)
    {
        minishell->env = new_var;
    }
    else
    {
        current = minishell->env;
        while (current->next)
            current = current->next;
        current->next = new_var;
    }
    
    // Update envp array
    update_envp_array(minishell, name, value);
}

static void export_without_value(t_minishell *minishell, char *name)
{
    t_env *current;
    t_env *new_var;
    
    if (!minishell || !name)
        return;
    
    // Check if variable already exists
    current = minishell->env;
    while (current)
    {
        if (current->name && ft_strcmp(current->name, name) == 0)
        {
            // Variable exists, don't change its value
            return;
        }
        current = current->next;
    }
    
    // Variable doesn't exist, create it without value
    new_var = malloc(sizeof(t_env));
    if (!new_var)
        return;
    
    new_var->name = ft_strdup(name);
    new_var->value = NULL;  // No value assigned
    new_var->next = NULL;
    
    if (!new_var->name)
    {
        free(new_var);
        return;
    }
    
    // Add to end of list
    if (!minishell->env)
    {
        minishell->env = new_var;
    }
    else
    {
        current = minishell->env;
        while (current->next)
            current = current->next;
        current->next = new_var;
    }
    
    // Don't add to envp if no value
}

