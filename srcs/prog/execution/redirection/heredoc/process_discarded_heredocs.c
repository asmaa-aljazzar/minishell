#include "minishell.h"

int process_discarded_heredocs(t_minishell *minishell, t_command *cmd)
{
    char *content;
    int should_expand;
    int i;
    
    if (!cmd)
        return (1);
    if (!cmd->input_files)
        return (1);
    i = 0;
    while (cmd->input_files[i])
    {
        should_expand = should_expand_heredoc(minishell, cmd->input_files[i]);
        content = read_heredoc_content(minishell, cmd->input_files[i], should_expand);
        if (!content)
        {
            if (g_signal_received == SIGINT)
            {
                g_signal_received = 0; // Reset signal
                minishell->exit_code = 130; // 128 + SIGINT(2)
            }
            else
                minishell->exit_code = 1;
            return (0);
        }
        free(content);
        i++;
    }
    return (1);
}