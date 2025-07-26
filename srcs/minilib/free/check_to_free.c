/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:25:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:35:31 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_to_free(t_minishell *minishell)
{
    if (minishell->cmd)
    {
        free_commands(minishell);
        minishell->cmd = NULL;
    }
    if (minishell->tok)
    {
        free_tokens(minishell->tok);
        minishell->tok = NULL;
    }
    if (minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
    }
}
