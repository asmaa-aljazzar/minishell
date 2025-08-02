
#include "minishell.h"

void free_token(t_token *token)
{
	if (!token)
		return;
	free(token->word);
	free(token);
}