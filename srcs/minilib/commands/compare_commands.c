
#include "minishell.h"


void compare_commands(t_minishell *shell)
{
        int     redir_status;

        redir_status = handell_redirection(shell);
        if (redir_status > 0) 
                exit(EXIT_SUCCESS);  // Pure redirection handled
        else if (redir_status < 0) 
                exit(EXIT_FAILURE);  // Redirection error
        // Handle normal commands...
        if (is_builtin(shell->cmd))
        {
                exec_builtin(shell);
                exit(shell->exit_code);
        }
        else
        {
                exec_command(shell);
                exit(EXIT_FAILURE);
        }
}