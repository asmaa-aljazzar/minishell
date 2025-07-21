/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_to_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:25:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/21 11:53:56 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void check_to_free(t_minishell *minishell)
{
    if (minishell->input && strcmp(minishell->input, "exit") == 0)
        ft_exit (minishell, "", 0);
    if (minishell->cmd)
    {
        free_commands(minishell);
        minishell->cmd = NULL;  // Add this
    }
    if (minishell->tok)
    {
        free_tokens(minishell->tok);
        minishell->tok = NULL;  // Add this
    }
    if (minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;  // Add this
    }
}