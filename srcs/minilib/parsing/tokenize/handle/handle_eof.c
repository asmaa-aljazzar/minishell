

#include "minishell.h"

void	handle_eof(t_minishell *minishell)
{
	if (!minishell->input)
	{
		printf("exit\n");
		free_env(minishell->env);
		free_2d(minishell->envp);
		rl_clear_history();
		exit(0);
	}
}

