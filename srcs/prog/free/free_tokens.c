
#include "minishell.h"

void free_tokens(t_token **tokens)
{
    int i = 0;

    if (!tokens)
        return;
    while (tokens[i])
    {
        free(tokens[i]->word);  
        free(tokens[i]);        
        i++;
    }
    free(tokens);
}