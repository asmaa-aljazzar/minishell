
#include "minishell.h"

void tokenize_pipe_op(t_minishell *minishell, int *k, int *i)
{
    minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
    if (!minishell->tok[*k])
        ft_exit(minishell, "Memory allocation failed", 1);
    minishell->tok[*k]->word = ft_strdup("|");
    minishell->tok[*k]->type = OUTPUT_PIPE;
    minishell->tok[*k]->qtype = QUOTE_NONE;
    (*k)++;
    (*i)++;
}