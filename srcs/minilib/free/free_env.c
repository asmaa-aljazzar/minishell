/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:03:13 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:09:16 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_env(t_env *env)
{
    t_env *current = env;
    t_env *next;

    while (current)
    {
        next = current->next;
        free(current->name);
        free(current->value);
        free(current);
        current = next;
    }
}