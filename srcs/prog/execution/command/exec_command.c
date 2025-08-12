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

#include "minishell.h"

// Returns 1 if command argv is empty or all whitespace
// This checks all args to be empty strings or whitespace only
static int is_command_empty_all(t_command *cmd)
{
    if (!cmd || !cmd->argv)
        return 1;

    for (int i = 0; cmd->argv[i]; i++)
    {
        char *arg = cmd->argv[i];
        while (*arg && (*arg == ' ' || *arg == '\t' || *arg == '\n'))
            arg++;
        if (*arg != '\0')
            return 0; // found non-empty arg
    }
    return 1;
}

int exec_command(t_minishell *ms)
{
    t_command *cmd = ms->cmd;
    int redir_status;

    if (!cmd || !cmd->argv)
    {
        ms->exit_code = 127;
        return -1;
    }

    // If no arguments at all, treat as empty, do nothing
    if (!cmd->argv[0])
    {
        ms->exit_code = 0;
        return 0;
    }

    // Check first argument empty string
    if (cmd->argv[0][0] == '\0')
    {
        // Check argv_expanded flag for first arg
        if (cmd->argv_expanded && cmd->argv_expanded[0] == 0)
        {
            // Literal empty string → print error
            ft_putstr_fd("minishell: : command not found\n", STDERR_FILENO);
            ms->exit_code = 127;
            return -1;
        }
        else
        {
            // Expanded empty → silent success
            ms->exit_code = 0;
            return 0;
        }
    }

    // Also treat commands where all argv are empty/whitespace only as empty
    if (is_command_empty_all(cmd))
    {
        ms->exit_code = 0;
        return 0;
    }

    // Handle redirections before execution
    // redir_status = handle_redirection(ms);
     redir_status = 0;
    if (redir_status != 0)
    {
        if (redir_status > 0)
            return 0; // redirection-only success
        return -1;    // redirection error
    }

    // Must have envp for execve
    if (!ms->envp)
    {
        ms->exit_code = 1;
        return -1;
    }

    // If builtin, handle accordingly (likely inside compare_commands)
    if (is_builtin(cmd))
    {
        compare_commands(ms);
        return 0; // builtins do not execve
    }

    // Otherwise execute external command (execve)
    // execute_external_command(ms);

    // If execve returns, error occurred
    return -1;
}
