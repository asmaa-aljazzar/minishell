#include "minishell.h"

void debug_command(const t_command *cmd)
{
    if (!cmd)
    {
        printf("[DEBUG] Command pointer is NULL.\n");
        return;
    }
    printf("---- Debugging Command at %p ----\n", (void *)cmd);
    // argv and argv_expanded
    if (cmd->argv)
    {
        printf("argv:\n");
        for (int i = 0; cmd->argv[i] != NULL; i++)
        {
            int expanded_flag = (cmd->argv_expanded) ? cmd->argv_expanded[i] : -1;
            printf("  argv[%d]: '%s'  | expanded: %d\n", i, cmd->argv[i], expanded_flag);
        }
    }
    else
        printf("argv is NULL\n");
    if (cmd->redir)
    {
        t_redirection *redir = cmd->redir;
        while (redir)
        {
            printf("Redirection type: %d, file: %s\n", redir->type, redir->file);
            redir = redir->next;
        }
    }
    else
    {
        printf("No redirections.\n");
    }

    printf("Next command pointer: %p\n", (void *)cmd->next);

    printf("-----------------------------------\n");
}

