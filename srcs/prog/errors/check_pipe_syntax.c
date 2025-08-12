#include "minishell.h"

int check_pipe_syntax(t_minishell *ms, int i)
{
    // Starts with pipe
    if (i == 0 && ms->tok[i] && ((ms->tok[i + 1] && ms->tok[i + 1]->type != PIPE) || !ms->tok[i + 1])) 
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
        ms->exit_code = 2;
        return (0);
    }
    // Ends with pipe
    if (!ms->tok[i + 1])
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `|'", 2);
        ms->exit_code = 2;
        return (0);
    }
    // Detect consecutive pipes
    if (ms->tok[i + 1] && ms->tok[i + 1]->type == PIPE)
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `||'", 2);
        ms->exit_code = 2;
        return (0);
    }
    return (1);
}