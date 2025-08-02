
#include "minishell.h"

void init_commands(t_minishell *minishell)
{
	t_command *head = NULL;
	t_command *curr = NULL;
	int count = minishell->pipe_count;
	int i = 0;

	while (i <= count)
	{
		t_command *new = create_command(minishell);
		if (!head)
		{
			head = new;
			curr = new;
		}
		else
		{
			curr->next = new;
			curr = new;
		}
		i++;
	}
	minishell->cmd = head;
}

