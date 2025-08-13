#include "minishell.h"

void setup_sig_exc(int sig, void(*handler)(int))
{
    struct sigaction sa;
    // fprintf(stderr, "here");
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART; // Restart syscalls like readline()
    sigaction(sig, &sa, NULL);
    // signal(SIGINT, SIG_DFL);
}

void setup_signals_child(void)
{
    setup_sig_exc(SIGINT, SIG_DFL);   // Ctrl+C kills the process
    setup_sig_exc(SIGQUIT,SIG_DFL);  // Ctrl+\ kills it
}
void handlequit(int sig)
{
    (void)sig;
    write(2, "Quit (core dumped)\n", 20);
}
void handle_c(int sig)
{
    (void)sig;
    write(1, "\n", 1);
}
