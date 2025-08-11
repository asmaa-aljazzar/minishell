
#include "minishell.h"

void	tokenize_normal_string(t_minishell *ms, int *k, int *i, int glued)
{
	int		start;
	int		length;
	char	*word;

	start = *i;
	while (ms->input[*i] && ms->input[*i] != ' ' && ms->input[*i] != '\''
		&& ms->input[*i] != '"' && ms->input[*i] != '>' && ms->input[*i] != '<'
		&& ms->input[*i] != '|')
		(*i)++;
	if (*i - start == 0)
		return ;
	length = *i - start;
	word = allocate_normal_word(ms, start, length);
	fill_normal_token(ms, word, glued, k);
	ms->last_token_end = start + length - 1;
}
