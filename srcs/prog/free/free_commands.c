
#include "minishell.h"

void free_redirections(t_redirection *redir)
{
	t_redirection *current;
	t_redirection *next;

	current = redir;
	while (current->next)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		free(current);
		current = next;
	}
}

void	free_commands(t_minishell *minishell)
{
	t_command	*current;
	t_command	*next;

	current = minishell->cmd;
	while (current)
	{
		next = current->next;
		if (current->argv)
			free(current->argv);
		// if (current->redir)
		// {
		// 	free_redirections(current->redir);
		// 	current->redir = NULL; // Avoid double free
		// }
		free(current);
		current = next;
	}
	minishell->cmd = NULL;
}
