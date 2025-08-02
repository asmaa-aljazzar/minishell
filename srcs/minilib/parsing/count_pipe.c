
#include "minishell.h"

void count_pipe(t_minishell *minishell)
{
    int i = 0;
    int pipes = 0;
    char *input = minishell->input;
    while (input[i])
    {
        if (input[i] == '|')
            pipes += 1;
        i++;
    }
    minishell->pipe_count = pipes;
}