#include "minishell.h"

void setup_signals_child(void)
{
    signal(SIGINT, SIG_DFL);   // Ctrl+C kills the process
    signal(SIGQUIT, SIG_IGN);  // Ctrl+\ Do nothing
}

