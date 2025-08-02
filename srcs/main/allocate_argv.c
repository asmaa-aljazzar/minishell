
#include "minishell.h"

// check if the token is not a redirection and argv inside one command
// not between pipes

void allocate_argv(t_minishell *minishell, int *argc, t_command **cmd, int *i)
{
	t_token *token = minishell->tok[*i];

	if (token->type == INPUT_PIPE || token->type == OUTPUT_PIPE)
	{
		(*cmd)->argv = malloc(sizeof(char *) * (*argc + 1));
		if (!(*cmd)->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
		*argc = 0;
		*cmd = (*cmd)->next;
	}
	else if (token->type != INPUT_FILE && token->type != INPUT_HEREDOC
		&& token->type != OUTPUT_FILE && token->type != OUTPUT_APPEND)
	{
		(*argc)++;
	}
}
