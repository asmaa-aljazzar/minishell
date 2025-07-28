/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:51:42 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:43:20 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_cmd_path( char *cmd,char *path_env)
{
    char    *full_path;
    char    *token;
    
    token = strtok(path_env, ":");
    while (token)
    {
        full_path = join_path(token, cmd);
        if (!full_path)
                return NULL;
        if (is_executable(full_path))
            return full_path; // found it
        free(full_path);
        token = strtok(NULL, ":");
    }
    return NULL;
}