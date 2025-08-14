#include "minishell.h"

void yaman(int sig)
{
    (void)sig;
    g_signal_received = SIGINT;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    close(0);
}

int read_heredoc_content(t_minishell *shell, char *delimiter, int should_expand)
{
    int fd[2];

    if (pipe(fd) == -1)
    {
        perror("pipe");
        return (-1);
    }
    struct sigaction sa;
    sa.sa_handler = yaman;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // Restart syscalls like readline()
    sigaction(SIGINT, &sa, NULL);
    read_until_delimiter(shell, delimiter, fd[1], should_expand);
    close(fd[1]); // Close write end of the pipe
    
    // fprintf(stderr, "%d\n", fd[0]);
    return (fd[0]);
}
