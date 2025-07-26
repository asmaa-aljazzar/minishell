/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:58:43 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 11:59:06 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(t_env *env, const char *var)
{
    while (env)
    {
        if (ft_strncmp(env->name, var, ft_strlen(env->name) + 1) == 0)
            return env->value;
        env = env->next;
    }
    return "";
}