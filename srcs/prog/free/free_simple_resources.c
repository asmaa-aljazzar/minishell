
#include "minishell.h"

void free_simple_resources(t_minishell *shell)
{
    if (shell->input)
    {
        free(shell->input);
        shell->input = NULL;
    }
}