#include "minishell.h"

int process_all_heredocs(t_minishell *minishell)
{
    t_command *cmd;

    cmd = minishell->cmd;
    while (cmd)
    {
        if (!process_discarded_heredocs(minishell, cmd))
            return (0);
            
        if (!process_final_heredoc(minishell, cmd))
            return (0);

        cmd = cmd->next;
    }
    return (1);
}
