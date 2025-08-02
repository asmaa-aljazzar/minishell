
#include "minishell.h"

void init(t_minishell *minishell)
{
    minishell->tok = NULL;
    minishell->input = NULL;
    minishell->cmd = NULL;
    minishell->tokens_count = 0;
    minishell->pipe_count = 0;
    ft_memset(minishell->buff, 0, sizeof(minishell->buff));
}
