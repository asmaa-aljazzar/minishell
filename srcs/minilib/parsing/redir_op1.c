/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_op1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:17:12 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/14 06:15:48 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redir_op1(t_minishell *minishell, int *k, int *i)
{
    if (minishell->input[*i] == '<')
    {
        if (minishell->input[*i + 1] == '<')
        {
            minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
            if (!minishell->tok[*k])
                ft_exit(minishell, "Memory allocation failed", 1);
            minishell->tok[*k]->word = ft_strdup("<<");
            minishell->tok[*k]->type = INPUT_HEREDOC;
            minishell->tok[*k]->qtype = QUOTE_NONE;
            (*k)++;
            (*i) += 2;
        }
        else
        {
            minishell->tok[*k] = ft_calloc(1, sizeof(t_token));
            if (!minishell->tok[*k])
                ft_exit(minishell, "Memory allocation failed", 1);
            minishell->tok[*k]->word = ft_strdup("<");
            minishell->tok[*k]->type = INPUT_FILE;
            minishell->tok[*k]->qtype = QUOTE_NONE;
            (*k)++;
            (*i)++;
        }
    }
    else if (minishell->input[*i] == '>')
        redir_op2(minishell, k, i);
}
