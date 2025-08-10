#include "minishell.h"

int update_glued(t_minishell *ms, int *i, int token_index)
{
    int glued;
    int start;
    int j;

    start = *i;
    glued = 1;
    if (token_index == 0)
    {
        ms->last_token_end = *i; // first token start
        return 0;  // first token never glued
    }
    // Check characters between previous token end and current token start
    j = ms->last_token_end + 1;
    while (j < start)
    {
        if (ms->input[j] == ' ' || ms->input[j] == '\t')
        {
            glued = 0;
            break;
        }
        j++;
    }
    return (glued);
}
