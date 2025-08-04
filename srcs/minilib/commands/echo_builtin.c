// echo_builtin.c
#include "minishell.h"

// Helper function to check if string is a valid -n flag
// Valid: -n, -nn, -nnn, etc.
// Invalid: -nm, -n123, etc.
static int is_valid_n_flag(char *str)
{
    int i = 0;
    
    if (str[i++] != '-')
        return (0);
    
    if (str[i] != 'n')
        return (0);
    
    // Check if all remaining characters are 'n'
    while (str[i])
    {
        if (str[i] != 'n')
            return (0);
        i++;
    }
    
    return (1);
}

void echo_builtin(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    int i = 1;
    int newline = 1;
    
    // Process all -n flags
    while (cmd->argv[i] && is_valid_n_flag(cmd->argv[i]))
    {
        newline = 0;
        i++;
    }
    
    // Print arguments
    while (cmd->argv[i])
    {
        ft_putstr_fd(cmd->argv[i], STDOUT_FILENO);
        if (cmd->argv[i + 1])
            ft_putstr_fd(" ", STDOUT_FILENO);
        i++;
    }
    
    if (newline)
        ft_putstr_fd("\n", STDOUT_FILENO);
    
    shell->exit_code = 0;
}