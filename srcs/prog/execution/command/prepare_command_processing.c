#include "minishell.h"

int prepare_command_processing(t_minishell *ms)
{
    if (!ms->input || !ms->tok)
        return 0;

    allocate_commands(ms);
    expand_tokens(ms);
    merge_words(ms);
    argv_for_commands(ms);
    fill_argvs(ms);
    tokens_to_commands(ms);

    return 1;
}
