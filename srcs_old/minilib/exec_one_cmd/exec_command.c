// #include "minishell.h"

// int exec_command(t_minishell *shell)
// {
//     int redir_status;

//     if (!shell || !shell->cmd)
//     {
//         shell->exit_code = 127;
//         return -1;
//     }

//     // Handle redirections first
//     redir_status = handle_redirection(shell);
//     if (redir_status != 0)
//     {
//         if (redir_status > 0)
//             return 0; // Redirection-only command succeeded
//         return -1;    // Redirection error
//     }

//     // Check environment (required for execve)
//     if (!shell->envp)
//     {
//         shell->exit_code = 1;
//         return -1;
//     }

//     // Delegate to the external command execution
//     execute_external_command(shell);
//     return -1; // Should not return if execve succeeds
// }

#include "minishell.h"

// exec_command.c
#include "minishell.h"

int exec_command(t_minishell *shell)
{
    int redir_status;

    if (!shell || !shell->cmd)
    {
        shell->exit_code = 127;
        return -1;
    }

    // Check if command is empty after expansion (like $Nonexist -> "")
    if (is_command_empty(shell->cmd))
    {
        // Don't execute anything, just return success like bash
        shell->exit_code = 0;
        return 0;
    }

    // Handle redirections first
    redir_status = handle_redirection(shell);
    if (redir_status != 0)
    {
        if (redir_status > 0)
            return 0; // Redirection-only command succeeded
        return -1;    // Redirection error
    }

    // Check environment (required for execve)
    if (!shell->envp)
    {
        shell->exit_code = 1;
        return -1;
    }

    // Delegate to the external command execution
    execute_external_command(shell);
    return -1; // Should not return if execve succeeds
}