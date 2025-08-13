#include "minishell.h"

volatile sig_atomic_t g_signal_received = SIG_NONE;
void sigint_handler_heredoc(int sig)
{
    (void)sig;
    g_signal_received = SIGINT;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_done = 1;
    close(0);
}


void setup_signals_heredoc(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler_heredoc; 
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; 

    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}
