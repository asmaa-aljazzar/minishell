// main_redirection.c - Updated
#include "minishell.h"

void main_redirection(t_minishell *shell)
{
    t_command *cmd = shell->cmd;
    
    if (!cmd)
        return;
    
    // Handle heredoc input
    if (cmd->input_type == INPUT_HEREDOC)
    {
        if (!setup_heredoc_input(cmd))
            exit(EXIT_FAILURE);
    }
    // Handle file input
    else if (cmd->input_type == INPUT_FILE)
    {
        input_redirection(cmd);
    }
    
    // Handle output redirection
    if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
    {
        handle_output_redirection(cmd);
    }
}