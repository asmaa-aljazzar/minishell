#include "minishell.h"
void handle_single_quoted_token(t_token *token, t_token **new_tokens, int *new_count)
{
    token->expanded = 0;
    new_tokens[(*new_count)++] = token;
}