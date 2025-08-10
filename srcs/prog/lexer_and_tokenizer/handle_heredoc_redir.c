
#include "minishell.h"

void handle_heredoc_redir(t_minishell *minishell, int *k, int *i)
{
	minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
	if (!minishell->tok[*k])
		ft_exit(minishell, "Memory allocation failed", 1);
	minishell->tok[*k]->word = ft_strdup("<<");
	if (!minishell->tok[*k]->word)
	{
		free (minishell->tok[*k]);
		ft_exit(minishell, "Memory allocation failed", 1);
	}
	minishell->tok[*k]->type = INPUT_HEREDOC;
	minishell->tok[*k]->qtype = QUOTE_NONE;
	(*k)++;
	(*i) += 2;
}