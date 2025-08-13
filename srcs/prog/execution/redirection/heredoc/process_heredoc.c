#include "minishell.h"

int process_heredoc(t_minishell *shell, char *delimiter)
{
    int read_fd;
    int should_expand;
      
    should_expand = should_expand_heredoc(shell, delimiter);
    read_fd = read_heredoc_content(shell, delimiter, should_expand);
    if (read_fd == -1)
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
    //cmd->input_file = content;
    return (read_fd);
}
