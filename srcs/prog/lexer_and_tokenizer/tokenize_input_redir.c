
#include "minishell.h"
void tokenize_input_redir(t_minishell *ms, int *k, int *i)
{
    if (ms->input[*i] == '<')
    {
        if (ms->input[*i + 1] == '<')
            handle_heredoc_redir(ms, k, i);
        else
            handle_input_file_redir(ms, k, i);
    }
    ms->last_token_end = *i - 1; // last consumed char index
}


