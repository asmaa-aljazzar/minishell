
#include "minishell.h"

void handle_output_append_redir(t_minishell *minishell, int *k, int *i)
{
	minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!minishell->tok[*k])
		ft_exit(minishell, "Memory allocation failed", 1);
	minishell->tok[*k]->word = ft_strdup(">>");
	minishell->tok[*k]->type = OUTPUT_APPEND;
	minishell->tok[*k]->qtype = QUOTE_NONE;
	(*k)++;
	(*i) += 2;
}