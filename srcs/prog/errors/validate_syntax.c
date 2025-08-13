#include "minishell.h"

int validate_syntax(t_minishell *ms)
{
    int i = 0;

    while (ms->tok[i])
    {
        if (ms->tok[i]->type == PIPE)
        {
            if (!check_pipe_syntax(ms, i))
                return (0);
        }
        else if ((ms->tok[i]->type == T_INPUT ||
                 ms->tok[i]->type == T_HEREDOC ||
                 ms->tok[i]->type == T_OUTPUT ||
                 ms->tok[i]->type == T_APPEND) && 
                 (ms->tok[i + 1] && ms->tok[i + 1]->type != PIPE))
        {
            if (!check_redirection_syntax(ms, &i))
                return (0);
        }
        i++;
    }
    return (1);
}
