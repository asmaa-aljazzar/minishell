
#include "minishell.h"

void count_pipe(t_minishell *ms)
{
    int i = 0;
    int pipes = 0;
    char *input = ms->input;
    while (input[i])
    {
        if (input[i] == '|')
            pipes += 1;
        i++;
    }
    ms->pipe_count = pipes;
}