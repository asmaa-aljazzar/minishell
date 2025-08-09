#include "minishell.h"
volatile sig_atomic_t g_signal_received = SIG_NONE;

static void sigint_handler_heredoc(int sig)
{
    (void)sig;
    g_signal_received = SIGINT;
    write(1, "\n", 1); // newline after ^C
}
void setup_signals_heredoc(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler_heredoc;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0; // no SA_RESTART, so ^C will break readline()
    sigaction(SIGINT, &sa, NULL);

    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+
}