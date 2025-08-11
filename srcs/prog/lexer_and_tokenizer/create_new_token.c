#include "minishell.h"

t_token	*create_new_token(t_minishell *ms, const char *word, int did_expand)
{
	t_token *new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		ft_exit(ms, "Memory allocation failed", 1);
	new_token->word = ft_strdup(word);
	if (!new_token->word)
	{
		free(new_token);
		ft_exit(ms, "Memory allocation failed", 1);
	}
	new_token->type = INPUT_WORD;
	new_token->qtype = QUOTE_NONE;
	new_token->glued = 0;
	new_token->expanded = did_expand;
	return (new_token);
}