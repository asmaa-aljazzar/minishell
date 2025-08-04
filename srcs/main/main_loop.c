#include "minishell.h"
// main_loop.c - Updated section
void main_loop(t_minishell *minishell)
{
    print_banner();
    while (1)
    {
        setup_signals();
        init_shell(minishell);
        if (!minishell->input || !minishell->tok)
            continue;
        exit_builtin(minishell);
        init_commands(minishell);
        expand_tokens(minishell);
        merge_words(minishell);
        argv_for_commands(minishell);
        tokens_to_commands(minishell);
        if (!validate_pipeline(minishell))  // Add validation
        {
            check_to_free(minishell);
            continue;
        }
        if (!process_all_heredocs(minishell))
        {
            check_to_free(minishell);
            continue;
        }
        execute_pipeline(minishell);  // Replace main_fork with execute_pipeline
        check_to_free(minishell);
    }
}