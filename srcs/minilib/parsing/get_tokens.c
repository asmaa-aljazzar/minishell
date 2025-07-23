/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:52:12 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/23 16:57:50 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_tokens(t_minishell *ms)
{
    size_t len = ft_strlen(ms->input);
    int i = 0;
    int k = 0;

    ms->tok = ft_calloc(len + 1, sizeof(t_token *));
    if (!ms->tok)
        ft_exit(ms, "malloc failed", 1);

    while (ms->input[i])
    {
        int glued = 1;  // Default to glued

        /* Skip leading blanks */
        if (ms->input[i] == ' ')
        {
            glued = 0;  // Next token is NOT glued
            while (ms->input[i] == ' ')
                i++;
        }
        
        if (!ms->input[i])
            break;

        // First token is never glued
        if (k == 0)
            glued = 0;

        if (ms->input[i] == '|')
            pipe_op(ms, &k, &i);
        else if (ms->input[i] == '<' || ms->input[i] == '>')
            redir_op1(ms, &k, &i);
        else
            quoted(ms, &k, &i, glued);
    }
    ms->tok[k] = NULL;
    ms->tokens_count = k;
}