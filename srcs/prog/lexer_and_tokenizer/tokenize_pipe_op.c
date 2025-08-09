
#include "minishell.h"

void tokenize_pipe_op(t_minishell *ms, int *k, int *i)
{
    ms->tok[*k] = ft_calloc(1, sizeof(t_token));
    if (!ms->tok[*k])
        ft_exit(ms, "Memory allocation failed", 1);
    ms->tok[*k]->word = ft_strdup("|");
    ms->tok[*k]->type = PIPE;
    ms->tok[*k]->qtype = QUOTE_NONE;
    (*k)++;
    (*i)++;
    ms->last_token_end = *i - 1;
}
