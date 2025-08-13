#include "minishell.h"

t_command	*init_command(t_minishell *ms)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		ft_exit(ms, "malloc failed", EXIT_FAILURE);
	new->argv = NULL;
	new->argv_expanded = NULL;
	new->redir = NULL;
	new->next = NULL;
	return (new);
}
