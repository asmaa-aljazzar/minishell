#include "minishell.h"
void main_loop(t_minishell *ms)
{   
    (void)ms;
    print_banner();
    while (1) 
    {
        setup_signals_readline(); // if signall recieved in setup each readline
        init_shell(ms); // initialize after and before readline 
         if (!ms->input || !ms->tok)
            continue; // if no input and tokens then its enter
        //init_commands(minishell); // initialize commands list // todo
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
// void main_loop(t_minishell *ms)
// {   

//         tokenize(ms);    // ms->tok gets filled
//         if (!ms->tok)    // empty line after tokenizing
//         {
//             cleanup_iteration(ms);
//             continue;
//         }

//         init_commands(ms);       // parse tokens into commands
//         expand_tokens(ms);
//         merge_words(ms);
//         argv_for_commands(ms);
//         tokens_to_commands(ms);

//         if (!validate_pipeline(ms))
//         {
//             cleanup_iteration(ms);
//             continue;
//         }

//         if (is_single_builtin_parent(ms)) // e.g. "exit", "cd", "export", "unset"
//         {
//             run_builtin_in_parent(ms);
//             cleanup_iteration(ms);
//             continue;
//         }

//         if (!process_all_heredocs(ms))
//         {
//             cleanup_iteration(ms);
//             continue;
//         }

//         execute_pipeline(ms);
//         cleanup_iteration(ms);
//     }
// }
