
#include "minishell.h"

void	fill_normal_token(t_minishell *ms, char *word, int glued, int *k)
{
	ms->tok[*k] = calloc(1, sizeof(t_token));
	if (!ms->tok[*k])
	{
		free(word);
		ft_exit(ms, "Memory allocation failed", 1);
	}
	ms->tok[*k]->word = word;
	ms->tok[*k]->type = INPUT_WORD;
	ms->tok[*k]->qtype = QUOTE_NONE;
	ms->tok[*k]->glued = glued;
	ms->tok[*k]->expanded = 0;
	(*k)++;
}
