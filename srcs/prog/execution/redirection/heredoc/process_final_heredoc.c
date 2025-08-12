#include "minishell.h"

int process_final_heredoc(t_minishell *shell, t_command *cmd)
{
    char *content;
    int should_expand;
    
    if (cmd->input_type != INPUT_HEREDOC || !cmd->input_file)
        return (1);
        
    should_expand = should_expand_heredoc(shell, cmd->input_file);
    content = read_heredoc_content(shell, cmd->input_file, should_expand);

    if (!content)
    {
        if (g_signal_received == SIGINT)
        {
            g_signal_received = 0; // Reset signal
            shell->exit_code = 130; // 128 + SIGINT(2)
        }
        else
            shell->exit_code = 1;
        return (0);
    }

    free(cmd->input_file);
    cmd->input_file = content;
    return (1);
}