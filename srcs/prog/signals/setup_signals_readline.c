#include "minishell.h"

void setup_signals_readline(void)
{
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}