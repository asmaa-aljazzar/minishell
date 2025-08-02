
#include "minishell.h"

void create_quoted_token(t_minishell *ms, int *k, char *word, char quote, int glued)
{
	ms->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!ms->tok[*k])
	{
		free(word);
		ft_exit(ms, "Memory allocation failed", 1);
	}
	ms->tok[*k]->word = word;
	ms->tok[*k]->type = INUPT_WORD;
	ms->tok[*k]->qtype = (quote == '"') ? QUOTE_DOUBLE : QUOTE_SINGLE;
	ms->tok[*k]->glued = glued;
	(*k)++;
}