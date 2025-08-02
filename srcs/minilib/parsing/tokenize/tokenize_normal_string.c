
#include "minishell.h"

void tokenize_normal_string(t_minishell *minishell, int *k, int *i, int glued)
{
	int start = *i;
	char *word;

	while (minishell->input[*i] && minishell->input[*i] != ' ' 
		&& minishell->input[*i] != '\'' && minishell->input[*i] != '"' 
		&& minishell->input[*i] != '>' && minishell->input[*i] != '<' 
		&& minishell->input[*i] != '|')
		(*i)++;

	if (*i - start == 0)
		return;

	word = allocate_normal_word(minishell, start, *i - start);
	init_normal_token(minishell, word, glued, k);
}

