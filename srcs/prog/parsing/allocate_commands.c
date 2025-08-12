
#include "minishell.h"
static t_command *create_command_list(t_minishell *ms, int count)
{
    t_command *head = NULL;
    t_command *curr = NULL;
    t_command *new;
    int i = 0;

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
    return head;
}

void allocate_commands(t_minishell *ms)
{
    ms->cmd = create_command_list(ms, ms->pipe_count);
}
