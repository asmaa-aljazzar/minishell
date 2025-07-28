/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   already_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:50:25 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:40:59 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *already_path(char *cmd)
{
    char    *cmd_found;
    cmd_found = NULL;
    if (ft_strchr(cmd, '/'))
    {
        if (is_executable(cmd))
        {
            cmd_found = ft_strdup(cmd);
            if(!cmd_found)
                return (NULL);
            return (cmd_found);
        }
    }
    return (NULL);
}