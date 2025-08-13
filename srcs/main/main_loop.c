#include "minishell.h"

void main_loop(t_minishell *ms)
{
    print_banner();
    while (1)
    {
        setup_signals_readline();
        init_shell(ms);

        if (!prepare_command_processing(ms))
            continue;

        execute_commands(ms);
        check_to_free(ms);
    }
}
