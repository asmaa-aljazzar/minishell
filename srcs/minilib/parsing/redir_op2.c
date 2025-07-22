/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_op2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:17:47 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 15:59:24 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_op2(t_minishell *minishell, int *k, int *i)
{
    if (minishell->input[*i + 1] == '>')
    {
        minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
        if (!minishell->tok[*k])
            ft_exit(minishell, "Memory allocation failed", 1);
        minishell->tok[*k]->word = ft_strdup(">>");
        minishell->tok[*k]->type = OUTPUT_APPEND;
        minishell->tok[*k]->qtype = QUOTE_NONE;
        (*k)++;
        (*i) += 2;
    }
    else
    {
        minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
        if (!minishell->tok[*k])
            ft_exit(minishell, "Memory allocation failed", 1);
        minishell->tok[*k]->word = ft_strdup(">");
        minishell->tok[*k]->type = OUTPUT_FILE;
        minishell->tok[*k]->qtype = QUOTE_NONE;
        (*k)++;
        (*i)++;
    }
}