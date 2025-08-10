
#include "minishell.h"

void init_shell(t_minishell *ms)
{
    ms->tok = NULL;               // tokens array
    ms->tokens_count = 0;         // number of tokens
    ms->pipe_count = 0;           // number of pipe
    ms->input = readline(PROMPT); // input line
    handle_eof(ms);
    if (*ms->input)
        add_history(ms->input);
    if (!*ms->input) // if enter
    {
        free(ms->input);
        ms->input = NULL;
        return;
    }
    if (g_signal_received == SIGINT)
         ms->exit_code = 130;
     g_signal_received = SIG_NONE; // reset for next prompt //? with signal
    if (!get_tokens(ms)) // syntax error.
    {
        free(ms->input);
        ms->input = NULL;
        return ; // continue prompt loop
    }
    if (!validate_syntax(ms))
    {
        check_to_free(ms);
        ms->exit_code = 2;
        return;
    }
    count_pipe(ms);
    debug_print_tokens(ms->tok);//!
}
