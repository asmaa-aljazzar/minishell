/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 14:45:29 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:43:52 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *find_path(t_env *env)
{
     while(env)    // find PATH in envp
    {
        if (strncmp(env->name, "PATH", 4) == 0)
            return (env->value);
        env = env->next;
    }
    fprintf(stderr, "PATH not found\n");
    return (NULL);
}