/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:52:12 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 15:59:32 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void get_tokens(t_minishell *minishell)
{
    size_t len = ft_strlen(minishell->input);
    minishell->tok = ft_calloc((len + 1), sizeof(t_token *));
    int i = 0, k = 0;

    while (minishell->input[i])
    {
        while (minishell->input[i] == ' ')
            i++;
        if (!minishell->input[i])
            break;
        if (minishell->input[i] == '|')
            pipe_op(minishell, &k, &i);
        else if (minishell->input[i] == '<' || minishell->input[i] == '>')
            redir_op1(minishell, &k, &i);
        else
        {
            quoted(minishell, &k, &i);
        }
    }
    minishell->tok[k] = NULL;
    minishell->tokens_count = k;
}
