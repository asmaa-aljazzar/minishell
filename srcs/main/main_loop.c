#include "minishell.h"
void main_loop(t_minishell *ms)
{   
    (void)ms;
    // setup_signals_parent(); // if signall recieved before the loop // todo
    print_banner();
    while (1) 
    {
        // setup_signals_parent(); // if signall recieved in parent
        init_shell(ms); // initialize after and before readline // todo
        // if (!minishell->input || !minishell->tok)
            // continue; // if no input and tokens then its enter
        // exit_builtin(minishell); // exit command // todo
        // init_commands(minishell); // initialize commands list // todo
        // debug_tokens(minishell); // todo //!
        // expand_tokens(minishell);// expand tokens into its value // todo
        // merge_words(minishell);// merge with/without spaces need to // todo
        // argv_for_commands(minishell);// word into argv array // todo
        // tokens_to_commands(minishell); // tokens to multi commands by '|' // todo
        // debug_commands(minishell);// todo //!
        // if (!validate_pipeline(minishell))  // Add validation // todo
        // {
        //     check_to_free(minishell); // todo
        //     continue;
        // }
        // handle redirection in parent // todo
        // todo
        // if (!process_all_heredocs(minishell))// heredoc //! set with redirection
        // {
        //     check_to_free(minishell);
        //     continue;
        // }
        // execute_pipeline(minishell); // if there is another command // todo
        // check_to_free(minishell); 
    }
}