#include "minishell.h"

int read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    read_until_delimiter(shell, delimiter, fd[1], should_expand);
    close(fd[1]); // Close write end of the pipe
    return (fd[0]);
}
