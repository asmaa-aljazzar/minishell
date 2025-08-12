
#include "minishell.h"

void count_pipe(t_minishell *ms)
{
    t_token **curr;
    int i;
    int count;

    i = 0;
    count = 0;
    curr = ms->tok;
    while(curr[i])
    {
        if (curr[i]->type == PIPE)
            count++;
        i++;
    }
// <<<<<<< HEAD
    ms->pipe_count = count;
// =======
//     ms->pipe_count = pipes;
// >>>>>>> be7c71c (split some functions)
}
