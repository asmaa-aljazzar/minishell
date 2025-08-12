#include "minishell.h"
void main_loop(t_minishell *ms)
{
    (void)ms;
    print_banner();
    while (1)
    {
        setup_signals_readline(); // if signall recieved in setup each readline
        init_shell(ms);           // initialize after and before readline
        if (!ms->input || !ms->tok)
            continue;          // if no input and tokens then its enter
        allocate_commands(ms); // initialize commands list
        expand_tokens(ms);     // expand tokens into its value
        merge_words(ms);       // merge with/without spaces need to
        // debug_print_tokens(ms->tok);//!
        argv_for_commands(ms); // word into argv array // todo
        fill_argvs(ms);        // copies token strings into argv arrays
        // t_command *cmd = ms->cmd; //!
        tokens_to_commands(ms);
        // while (cmd)//!
        // {
        //     debug_command(cmd);
        //     cmd = cmd->next;
        // }//!
        // if (!validate_pipeline(minishell)) validation //  todo may not do
        // {
        //     check_to_free(minishell);
        //     continue;
        // }
        if (!process_all_heredocs(ms))// heredoc
        {
             check_to_free(ms);
             continue;
        }
        if (ms->pipe_count == 0)
            execute_single_command(ms); // todo
        else
            execute_piped_commands(ms, ms->pipe_count + 1); // todo
        check_to_free(ms);
    }
}