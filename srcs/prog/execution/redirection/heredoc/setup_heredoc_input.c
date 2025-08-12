#include "minishell.h"
int setup_heredoc_input(t_command *cmd)
{
    int heredoc_fd;
    // if (cmd->input_type != INPUT_HEREDOC || !cmd->input_file)
    //     return (0);
    // heredoc_fd = create_heredoc_pipe(cmd->input_file);
    (void)cmd;
    heredoc_fd = -1;
    if (heredoc_fd >= 0)
    {
        if (dup2(heredoc_fd, STDIN_FILENO) == -1)
        {
            close(heredoc_fd);
            return (0);
        }
        close(heredoc_fd);
        return (1);
    }
    return (0);
}
