#include "minishell.h"

void handle_first_split_token(t_token *token, const char *word, int did_expand,
                                     t_token **new_tokens, int *new_count)
{
    free(token->word);
    token->word = ft_strdup(word);
    if (!token->word)
        return ;    //TODO: add the free here
    token->qtype = QUOTE_NONE;
    token->expanded = did_expand;
    new_tokens[(*new_count)++] = token;
}