/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:25:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 16:12:38 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void check_to_free(t_minishell *minishell)
{
    // Remove this check - handle exit elsewhere
    // if (minishell->input && strcmp(minishell->input, "exit") == 0)
    //     ft_exit (minishell, "", 0);
    
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
