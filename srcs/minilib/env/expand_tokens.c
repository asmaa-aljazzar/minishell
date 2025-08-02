
#include "minishell.h"

void expand_tokens(t_minishell *minishell)
{
    int i = 0;
    char *expanded;
    t_token **tokens = minishell->tok;
    if (!tokens)
        return ;
    while (tokens[i])
    {
        if (tokens[i]->qtype != QUOTE_SINGLE)
        {
            if (tokens[i]->word)
            {
                expanded = expand_variable(minishell, tokens[i]->word);
                if (!expanded)
                    ft_exit(minishell, "Memory allocation failure during expansion", 1);
                free(tokens[i]->word);
                tokens[i]->word = expanded;
            }
        }
        i++;
    }
}
