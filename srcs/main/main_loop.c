#include "minishell.h"

int prepare_command_processing(t_minishell *ms)
{
    if (!ms->input || !ms->tok)
        return 0;

    expand_tokens(ms);
    count_pipe(ms);
    allocate_commands(ms);
    merge_words(ms);
    argv_for_commands(ms);
    fill_argvs(ms);
    tokens_to_commands(ms);

    return 1;
}

void execute_commands(t_minishell *ms)
{
    if (!process_all_heredocs(ms))
        return;

    if (ms->pipe_count == 0)
        execute_single_command(ms);
    else
        execute_piped_commands(ms, ms->pipe_count + 1);
}

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
