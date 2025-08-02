
#include "minishell.h"

void main_redirection(t_minishell *shell)
{
    t_command *cmd;

    cmd = shell->cmd;
    while (cmd)
    {
        if (cmd->input_type == INPUT_FILE)
            input_redirection(cmd);
        if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
            handle_output_redirection(cmd);
        // if (handle_empty_cmd(shell))
        // {
        //     cmd = cmd->next;
        //     continue;
        // }
        cmd = cmd->next; // move to next command
    }
}