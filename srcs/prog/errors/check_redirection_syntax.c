#include "minishell.h"

int check_redirection_syntax(t_minishell *ms, int *i)
{
    if (ms->tok[*i] && (!ms->tok[*i + 1] || ms->tok[*i + 1]->type != T_WORD))
    {
        ft_putendl_fd("minishell: syntax error near unexpected token `<>'", 2);
        ms->exit_code = 2;
        return 0;
    }
    (*i)++; // skip filename token
    return 1;
}
