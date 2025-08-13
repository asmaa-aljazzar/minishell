#include "minishell.h"

int	expand_tokens(t_minishell *ms)
{
	int	new_count;
	int	max_tokens;
	int	i;
	t_token **new_tokens; // new buffer to malloc
	
	i = 0;
	new_count = 0;
	if (!ms->tok)
		return (-1);
	max_tokens = count_max_tokens_after_expansion(ms);
		// Allocate new token array with room for splits
	new_tokens = ft_calloc(max_tokens + 1, sizeof(t_token *));
	if (!new_tokens)
		ft_exit(ms, "Memory allocation failed", 1);
	// Process each token
	while (ms->tok[i])
	{
		expand_and_split_token(ms, ms->tok[i], new_tokens, &new_count);
			// here we expand token
		i++;
	}
	new_tokens[new_count] = NULL;
	free(ms->tok);
	ms->tok = new_tokens; // Replace old tokens with new ones
	ms->tokens_count = new_count;
	return (0);
}
