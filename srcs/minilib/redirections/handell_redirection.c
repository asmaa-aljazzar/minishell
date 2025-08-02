
#include "minishell.h"
int handell_redirection_output(t_minishell *shell)
{
      // Handle output redirection (> or >>)
    if (shell->cmd->output_type == OUTPUT_FILE || 
        shell->cmd->output_type == OUTPUT_APPEND)
    {
        // For existing files, check write permissions
        if (access(shell->cmd->output_file, F_OK) == 0 && 
            access(shell->cmd->output_file, W_OK) != 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            perror(shell->cmd->output_file);
            return -1;
        }
        return 1;  // Output redirection OK
    }
    return (0);
}
int handell_redirection_input_herdoc(t_minishell *shell)
{
    if (shell->cmd->input_type == INPUT_FILE)
    {
        if (access(shell->cmd->input_file, R_OK) != 0)
        {
            ft_putstr_fd("minishell: ", STDERR_FILENO);
            perror(shell->cmd->input_file);
            return -1;
        }
        return 1;  // Input redirection OK
    }

    // Handle heredoc (<<)
    if (shell->cmd->input_type == INPUT_HEREDOC)
        return 1;  // Heredoc handled elsewhere
    return(0);
}
/*
** Handles cases with only redirections (no command)
** Returns 1 if pure redirection was handled
** Returns 0 if this was not a pure redirection case
** Returns -1 if there was an error
*/
int handell_redirection(t_minishell *shell)
{
    if (!shell->cmd || (shell->cmd->argv && shell->cmd->argv[0]))
        return 0;  // Not a pure redirection case

    // Handle output redirection (> or >>)
    if (shell->cmd->output_type == OUTPUT_FILE || 
        shell->cmd->output_type == OUTPUT_APPEND)
        {
            if(handell_redirection_output(shell))
                return 1;
        }
    if (shell->cmd->input_type == INPUT_FILE
            || shell->cmd->input_type == INPUT_HEREDOC)
    {
        if(handell_redirection_input_herdoc(shell))
            return 1;
    } 

    return 0;  // Not a pure redirection case
}