/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_output_filesAppend.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:28:59 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/27 18:14:01 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void if_output_filesAppend(t_minishell *minishell, t_token *token, t_command **cmd, int *i)
{
    if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
    {
        if (minishell->tok[(*i) + 1])
        {
            char *file = minishell->tok[++(*i)]->word;
            if (has_more_redirections(minishell->tok, *i + 1, OUTPUT_FILE, OUTPUT_APPEND))
                (*cmd)->output_files = add_to_list((*cmd)->output_files, file);
            else
            {
                (*cmd)->output_type = token->type;
                (*cmd)->output_file = ft_strdup(file); // FIX: Duplicate this too
            }
        }
    }
}