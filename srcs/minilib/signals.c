#include "minishell.h"
#include <signal.h>

void handle_sigint(int signum)
{
    (void)signum;
    g_signal_received = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void handle_sigquit(int signum)
{
    (void)signum;
}

void setup_signals_parent(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void setup_signals_child(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

void setup_signals_heredoc(void)
{
    signal(SIGINT, SIG_DFL);  // Allow Ctrl+C to terminate heredoc
    signal(SIGQUIT, SIG_IGN); // Ignore Ctrl+\ during heredoc
}