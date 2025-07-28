/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:49:23 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:52:45 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// builds a string: dir + "/" + cmd
char *join_path(const char *path, const char *cmd)
{
    size_t    len; 
    char    *full_path;

    len = ft_strlen(path) + ft_strlen(cmd) + 2;// +1 for '/' +1 for '\0'
    full_path = malloc(len);
    if (!full_path)
        return NULL;
    snprintf(full_path, len, "%s/%s", path, cmd); //DEBUGING
    return (full_path);
}