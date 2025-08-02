
#include "minishell.h"

void merge_words(t_minishell *minishell)
{
	t_token **orig;
	int i;
	int k;
    
    i = 0;
    k = 0;
	if (!minishell || !minishell->tok)
		return;
	orig = minishell->tok;
	while (orig[i])
	{
		minishell->tok[k] = orig[i];
		advance_and_merge(minishell, orig, &i, k);
		k++;
		i++;
	}
	minishell->tok[k] = NULL;
	minishell->tokens_count = k;
}
