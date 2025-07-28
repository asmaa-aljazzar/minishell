/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:46:30 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:32:18 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    printf("Executing: %s\n", cmd_path);
    for (int i = 0; shell->cmd->argv[i]; i++)
    printf("argv[%d]: %s\n", i, shell->cmd->argv[i]);

    execve(cmd_path, shell->cmd->argv,shell->envp);
    perror("execve");
    free(cmd_path);
    return -1;
}