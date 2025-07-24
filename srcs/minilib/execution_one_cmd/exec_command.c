/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:46:30 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/24 14:46:45 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_command(t_minishell *shell)
{
    char *cmd_path;
    char **envp;

    cmd_path = get_path(shell);
    if (!cmd_path)
        return -1;
    printf("%s",cmd_path);
    envp = env_to_envp(shell->env);
    if (!envp)
    {
        free(cmd_path);
        return -1;
    }
    printf("Executing: %s\n", cmd_path);
    for (int i = 0; shell->cmd->argv[i]; i++)
    printf("argv[%d]: %s\n", i, shell->cmd->argv[i]);

    execve(cmd_path, shell->cmd->argv, envp);
    perror("execve");
    free(cmd_path);
    free_2d(envp);
    return -1;
}