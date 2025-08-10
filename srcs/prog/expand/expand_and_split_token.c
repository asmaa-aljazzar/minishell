#include "minishell.h"

void expand_and_split_token(t_minishell *ms, t_token *token,
                            t_token **new_tokens, int *new_count)
{
    if (token->qtype == QUOTE_SINGLE)
    {
        handle_single_quoted_token(token, new_tokens, new_count);
        return;
    }
    char *expanded = expand_variable(ms, token->word);
    if (!expanded)
        ft_exit(ms, "Memory allocation failure during expansion", 1);
    int did_expand = (ft_strcmp(expanded, token->word) != 0);
    if (token->qtype == QUOTE_DOUBLE)
    {
        handle_double_quoted_token(token, expanded, new_tokens, new_count, did_expand);
    }
    else
    {
        handle_unquoted_token(ms, token, expanded, new_tokens, new_count, did_expand);
    }
}
