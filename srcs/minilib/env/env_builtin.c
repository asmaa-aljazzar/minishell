/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 14:49:10 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 17:23:49 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void env_builtin(t_minishell *minishell)
{
    t_env *curr = minishell->env;
    printf("call env\n");
    while (curr)
    {
        if (curr->value)
            printf("%s=%s\n", curr->name, curr->value);
        curr = curr->next;
    }
}
