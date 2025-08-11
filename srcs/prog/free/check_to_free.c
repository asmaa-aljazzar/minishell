
#include "minishell.h"

void	check_to_free(t_minishell *minishell)
{
	if (minishell->cmd)
	{
		free_commands(minishell);
		minishell->cmd = NULL;
	}
	if (minishell->tok)
	{
		free_tokens(minishell->tok);
		minishell->tok = NULL;
	}
	if (minishell->input)
	{
		free(minishell->input);
		minishell->input = NULL;
	}
}
