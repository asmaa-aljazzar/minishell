/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:46:33 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:50:00 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// checks if is executable
int is_executable(char *path)
{
    if (access(path, X_OK) == 0)
        return (1);
        
    return (0);
}