#include "minishell.h"

void handle_first_split_token(t_token *token, const char *word,
                              int did_expand, t_token_out *out)
{
    free(token->word);
    token->word = ft_strdup(word);
    if (!token->word)
        return; // TODO: add free here
    token->qtype = QUOTE_NONE;
    token->expanded = did_expand;
    out->new_tokens[(*out->new_count)++] = token;
}