
#include "minishell.h"

void	ft_exit(t_minishell *shell, char *msg, int status)
{
	if (msg && *msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	free_complex_resources(shell);
	free_simple_resources(shell);
	rl_clear_history();
	shell->exit_code = status;
	exit(status);
}
