
#include "minishell.h"

void	merge_two_tokens(t_minishell *minishell, t_token *dst, t_token *src)
{
	char *joined_word = ft_strjoin(dst->word, src->word);
	if (!joined_word)
		ft_exit(minishell, "malloc failed", 1);
	free(dst->word);
	dst->word = joined_word;
	free_token(src);
}