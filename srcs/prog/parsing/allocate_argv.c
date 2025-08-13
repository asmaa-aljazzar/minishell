#include "minishell.h"

void	allocate_argv(t_minishell *minishell, int *argc, t_command **cmd,
		int *i)
{
	t_token	*token;

	token = minishell->tok[*i];
	if (token->type == PIPE)
	{
		// Allocate argv and argv_expanded arrays for the current command
		(*cmd)->argv = malloc(sizeof(char *) * ((*argc) + 1));
		(*cmd)->argv_expanded = malloc(sizeof(int) * ((*argc) + 1));
		if (!(*cmd)->argv || !(*cmd)->argv_expanded)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
		*argc = 0;
		*cmd = (*cmd)->next;
	}
	else if (token->type != T_INPUT && token->type != T_HEREDOC
		&& token->type != T_OUTPUT && token->type != T_APPEND)
	{
		(*argc)++;
	}
}
