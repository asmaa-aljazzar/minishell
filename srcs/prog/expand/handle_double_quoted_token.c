#include "minishell.h"

void	handle_double_quoted_token(t_token *token, char *expanded,
		t_token **new_tokens, int *new_count, int did_expand)
{
	free(token->word);
	token->word = expanded;
	token->expanded = did_expand;
	new_tokens[(*new_count)++] = token;
}