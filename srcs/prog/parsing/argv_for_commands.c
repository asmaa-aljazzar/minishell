#include "minishell.h"

void	argv_for_commands(t_minishell *minishell)
{
	t_command	*cmd;
	int			i;
	int			argc;

	cmd = minishell->cmd;
	i = 0;
	argc = 0;
	while (minishell->tok[i])
	{
		allocate_argv(minishell, &argc, &cmd, &i);
		i++;
	}
	// Allocate argv and argv_expanded for the last command, if any
	if (cmd)
	{
		cmd->argv = malloc(sizeof(char *) * (argc + 1));
		cmd->argv_expanded = malloc(sizeof(int) * (argc + 1));
		if (!cmd->argv || !cmd->argv_expanded)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
	}
}
