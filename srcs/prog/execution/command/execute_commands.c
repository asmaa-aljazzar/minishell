#include "minishell.h"

void execute_commands(t_minishell *ms)
{
    if (!process_all_heredocs(ms))
        return;
    if (ms->pipe_count == 0)
        execute_single_command(ms);
    else
        execute_piped_commands(ms, ms->pipe_count + 1);
}
