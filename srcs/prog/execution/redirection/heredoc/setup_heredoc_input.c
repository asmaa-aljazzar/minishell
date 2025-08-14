#include "minishell.h"
int setup_heredoc_input(t_redirection *redir)
{
    int heredoc_fd;

    heredoc_fd = redir->heredoc_fd;
    // fprintf(stderr, "%d\n", redir->heredoc_fd);
    if (heredoc_fd >= 0)
    {
        if (dup2(heredoc_fd, 0) == -1)
        {
            close(heredoc_fd);
            return (-1);
        }
        close(heredoc_fd);
    }
    return (0);
}
