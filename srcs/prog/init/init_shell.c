
#include "minishell.h"

// void	init_shell(t_minishell *ms)
// {
// 	ms->tok = NULL;               // tokens array
// 	ms->tokens_count = 0;         // number of tokens
// 	ms->pipe_count = 0;           // number of pipe
// 	ms->input = readline(PROMPT); // input line
// 	if (!ms->input)
// 		handle_eof(ms);
// 	if (!*ms->input) // if enter
// 	{
// 		free(ms->input);
// 		ms->input = NULL;
// 		return ;
// 	}
// 	add_history(ms->input);
// 	if (g_signal_received == SIGINT)
// 		ms->exit_code = 130;
// 	g_signal_received = SIG_NONE; // reset for next prompt //? with signal
// 	if (!get_tokens(ms))          // syntax error.//todo
// 	{
// 		free(ms->input);
// 		ms->input = NULL;
// 		return ; // continue prompt loop
// 	}
// 	if (!validate_syntax(ms))//todo
// 	{
// 		check_to_free(ms);
// 		ms->exit_code = 2;
// 		return ;
// 	}
// }

static int read_input_and_process(t_minishell *ms)
{
    ms->input = readline(PROMPT);
    if (!ms->input)
    {
        handle_eof(ms);
        return 0;
    }
    if (!*ms->input)
    {
        free(ms->input);
        ms->input = NULL;
        return 0;
    }
    add_history(ms->input);

    if (g_signal_received == SIGINT)
        ms->exit_code = 130;
    g_signal_received = SIG_NONE;

    return 1;
}

static int read_and_prepare_input(t_minishell *ms)
{
    initialize_fields(ms);
    return read_input_and_process(ms);
}


static int process_input_and_validate(t_minishell *ms)
{
    if (!get_tokens(ms))
    {
        free(ms->input);
        ms->input = NULL;
        return 0;
    }
    if (!validate_syntax(ms))
    {
        check_to_free(ms);
        ms->exit_code = 2;
        return 0;
    }
    return 1;
}

int init_shell(t_minishell *ms)
{
    if (!read_and_prepare_input(ms))
        return (1);

    if (!process_input_and_validate(ms))
        return (1);
    return (0);
}

