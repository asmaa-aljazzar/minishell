
#include "minishell.h"

int validate_syntax(t_minishell *ms)
{
    int i = 0;

    while (ms->tok[i])
    {
        if (ms->tok[i]->type == PIPE)
        {
            // Starts with pipe
            if (i == 0 && ms->tok[i]->type != PIPE)
            {
                ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
                ms->exit_code = 2;
                return 0;
            }

            // Ends with pipe
            if (!ms->tok[i + 1])
            {
                ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
                ms->exit_code = 2;
                return 0;
            }

            // Detect consecutive pipes (||, |||, etc.)
            if (ms->tok[i + 1] && ms->tok[i + 1]->type == PIPE)
            {
                // Count how many consecutive pipes
                int j = i + 1;
                while (ms->tok[j] && ms->tok[j]->type == PIPE)
                    j++;

                ft_putendl_fd("minishell: syntax error near unexpected token `||'", 2);
                ms->exit_code = 2;
                return 0;
            }
        }

        // Redirection check
        else if (ms->tok[i]->type == INPUT_FILE ||
                 ms->tok[i]->type == INPUT_HEREDOC ||
                 ms->tok[i]->type == OUTPUT_FILE ||
                 ms->tok[i]->type == OUTPUT_APPEND)
        {
            if (!ms->tok[i + 1] || ms->tok[i + 1]->type != INPUT_WORD)
            {
                ft_putendl_fd("minishell: syntax error near unexpected token `<>'", 2);
                ms->exit_code = 2;
                return 0;
            }
            i++; // skip filename token
        }

        i++;
    }

    return 1;
}

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
    // if (g_signal_received == SIGINT) //? with signal
    //     minishell->exit_code = 130;
    // else if (g_signal_received == SIGQUIT) //? with signal
    //     minishell->exit_code = 131;
    // g_signal_received = SIG_NONE; // reset for next prompt //? with signal
    if (!get_tokens(ms)) // syntax error.
    {
        free(ms->input);
        ms->input = NULL;
        return ; // continue prompt loop
    }
    debug_print_tokens(ms->tok);//!
    // if (!validate_syntax(minishell))
    // {
    //     check_to_free(minishell);
    //     minishell->exit_code = 2;
    //     return;
    // }
    // count_pipe(minishell);
}
