

#include "minishell.h"

void	handle_eof(t_minishell *minishell)
{
	write(1, "exit\n", 5);
	free_env(minishell->env);
	free_2d(minishell->envp);
	rl_clear_history();
	exit(0);
}

