
#include "minishell.h"
//static 
t_command *create_command_list(t_minishell *ms, int count)
{
    t_command *head = NULL;
    t_command *curr = NULL;
    t_command *new;
    int i = 0;
}

void	allocate_commands(t_minishell *ms) //todo 25 line norm error
{
	t_command	*head;
	t_command	*curr;
	int			count;
	int			i;
	t_command	*new;

	head = NULL;
	curr = NULL;
	count = ms->pipe_count;
	i = 0;
	while (i <= count)
	{
		new = init_command(ms);
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

// void allocate_commands(t_minishell *ms) this function adds extra step only
// {
//     ms->cmd = create_command_list(ms, ms->pipe_count); 
// }
