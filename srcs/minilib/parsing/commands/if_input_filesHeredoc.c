/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_input_filesHeredoc.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:21:14 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/27 17:57:58 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void if_input_filesHeredoc(t_minishell *minishell, t_token *token, t_command **cmd, int *i)
{
    if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
    {
        if (minishell->tok[(*i) + 1])
        {
            char *file = minishell->tok[++(*i)]->word;
            if (has_more_redirections(minishell->tok, *i + 1, INPUT_FILE, INPUT_HEREDOC))
                (*cmd)->input_files = add_to_list((*cmd)->input_files, file);
            else
            {
                (*cmd)->input_type = token->type;
                (*cmd)->input_file = ft_strdup(file);
            }
        }
    }
}