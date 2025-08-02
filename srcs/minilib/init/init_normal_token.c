
#include "minishell.h"

void init_normal_token(t_minishell *ms, char *word, int glued, int *k)
{
	ms->tok[*k] = calloc(1, sizeof(t_token));
	if (!ms->tok[*k])
	{
		free(word);
		ft_exit(ms, "Memory allocation failed", 1);
	}

	ms->tok[*k]->word = word;
	ms->tok[*k]->type = INUPT_WORD;
	ms->tok[*k]->qtype = QUOTE_NONE;
	ms->tok[*k]->glued = glued;
	(*k)++;
}