
#include "minishell.h"

char *allocate_normal_word(t_minishell *ms, int start, int len)
{
	char *word = calloc(1, len + 1);
	if (!word)
		ft_exit(ms, "Memory allocation failed", 1);
	ft_strlcpy(word, &ms->input[start], len + 1);
	return word;
}