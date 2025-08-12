#include "minishell.h"

void handle_double_quoted_token(t_token *token, char *expanded,
                               t_token_out *out, int did_expand)
{
    free(token->word);
    token->word = expanded;
    token->expanded = did_expand;
    out->new_tokens[(*out->new_count)++] = token;
}