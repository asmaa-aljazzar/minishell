#include "minishell.h"

void setup_signals_execution(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_IGN);
}