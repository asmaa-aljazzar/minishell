#include "minishell.h"

void setup_signals_parent(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Restart syscalls like readline()
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+
}