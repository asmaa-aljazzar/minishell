
#include "minishell.h"


int exec_command(t_minishell *shell)
{
    char *cmd_path;
    int redir_status;

    // // Handle pure redirections first
    redir_status = handell_redirection(shell);
    if (redir_status != 0)
    {
        if (redir_status > 0)
            return 0;  // Success case
        return -1; // Error case
    }
    cmd_path = get_path(shell);
    if (!cmd_path)
        return -1;
    if (!shell->envp)
    {
        free(cmd_path);
        return -1;
    }
    // printf("Executing: %s\n", cmd_path);
    int i;
    i = 0;
    while (shell->cmd->argv[i])
     i++;
    // printf("argv[%d]: %s\n", i, shell->cmd->argv[i]);

    execve(cmd_path, shell->cmd->argv,shell->envp);
    perror("execve");
    free(cmd_path);
    return -1;
}