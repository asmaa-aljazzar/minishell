/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:10 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 15:58:46 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void env_builtin(t_minishell *minishell)
{
    t_env *curr = minishell->env;
    while (curr)
    {
        if (curr->value)
            printf("%s=%s\n", curr->name, curr->value);
        curr = curr->next;
    }
}
