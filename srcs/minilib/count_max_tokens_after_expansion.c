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
    if (max > 0)
        return max;
    else
        return 100; // Minimum allocation
}