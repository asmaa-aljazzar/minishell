/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:40:59 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:44:42 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *get_path(t_minishell *shell)
{
    char    *path_env;
    char    *path_copy;
    char    *path;
    t_command   *cmd ;

    path_env = NULL;
    path_copy = NULL;
    cmd = shell->cmd;
    if (!cmd || !cmd->argv || !cmd->argv[0])
        return (NULL);

// if (!cmd) {
//     printf("Debug: cmd is NULL\n");
//     return NULL;
// }
// if (!cmd->argv) {
//     printf("Debug: cmd->argv is NULL\n");
//     return NULL;
// }
// if (!cmd->argv[0]) {
//     printf("Debug: cmd->argv[0] is NULL\n");
//     return NULL;
// }
// if (cmd->argv[0][0] == '\0') {
//     printf("Debug: cmd->argv[0] is empty string\n");
//     return NULL;
// }

// printf("Debug: command to execute is '%s'\n", cmd->argv[0]);

    if((path =already_path(cmd->argv[0]))) //if input is already  /usr/bin/cat
    {
            if(!path)
                return (NULL);
        return(path);
    }
    path_env = find_path(shell->env); // get raw PATH string
    if (!path_env)
        return (NULL);
    path_copy = ft_strdup(path_env);
    if (!path_copy)
        return (NULL);
    path = find_cmd_path(cmd->argv[0], path_copy);
        free(path_copy);
    return (path);
}