
#include "minishell.h"

void allocate_commands(t_minishell *ms)
{
	t_command *head;
	t_command *curr;
	int count;
	int i;
	
	head = NULL;
	curr = NULL;
	count = ms->pipe_count;
	i = 0;
	while (i <= count)
	{
		t_command *new = init_command(ms);
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
	ms->cmd = head;
}

