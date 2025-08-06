#include "minishell.h"

int count_max_tokens_after_expansion(t_minishell *ms)
{
    int i = 0;
    int max = 0;
    
    while (ms->tok && ms->tok[i])
    {
        if (ms->tok[i]->qtype == QUOTE_SINGLE)
            max += 1; // No expansion
        else
            max += 20; // Conservative estimate for potential splits
        i++;
    }
    return (max > 0) ? max : 100; // Minimum allocation
}

void expand_tokens(t_minishell *minishell)
{
    t_token **new_tokens;
    int new_count = 0;
    int i = 0;
    
    if (!minishell->tok)
        return;
    
    // Allocate new token array with room for splits
    int max_tokens = count_max_tokens_after_expansion(minishell);
    new_tokens = ft_calloc(max_tokens + 1, sizeof(t_token *));
    if (!new_tokens)
        ft_exit(minishell, "Memory allocation failed", 1);
    
    // Process each token
    while (minishell->tok[i])
    {
        expand_and_split_token(minishell, minishell->tok[i], 
                              new_tokens, &new_count);
        i++;
    }
    
    new_tokens[new_count] = NULL;
    
    // Replace old tokens with new ones
    free(minishell->tok); // Don't free individual tokens - they're reused
    minishell->tok = new_tokens;
    minishell->tokens_count = new_count;
}