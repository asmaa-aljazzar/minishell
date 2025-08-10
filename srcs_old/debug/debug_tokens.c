#include "minishell.h"
// In your main_loop or wherever you call get_tokens
void debug_tokens(t_minishell *minishell)
{
    printf("=== DEBUG TOKENS ===\n");
    printf("Input: '%s'\n", minishell->input);
    printf("Number of tokens: %d\n", minishell->tokens_count);
    
    for (int i = 0; minishell->tok && minishell->tok[i]; i++)
    {
        printf("Token[%d]: word='%s' | type=%d | qtype=%d | glued=%d\n", 
               i, 
               minishell->tok[i]->word, 
               minishell->tok[i]->type, 
               minishell->tok[i]->qtype,
               minishell->tok[i]->glued);
    }
    printf("===================\n");
}