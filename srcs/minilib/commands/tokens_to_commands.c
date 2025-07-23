/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:03:54 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/23 14:05:12 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void tokens_to_commands(t_minishell *minishell)
{
    t_command *cmd = minishell->cmd;
    int i = 0;
    int argc = 0;

    while (minishell->tok[i])
    {
        t_token *token = minishell->tok[i];

        if (ft_strncmp(token->word, "|", 1) == 0)
        {
            cmd->argv[argc] = NULL;
            cmd = cmd->next;
            argc = 0;
        }
        else if (token->type == INPUT_FILE || token->type == INPUT_HEREDOC)
        {
            cmd->input_type = token->type;
            if (minishell->tok[i + 1])
                cmd->input_file = minishell->tok[++i]->word;
        }
        else if (token->type == OUTPUT_FILE || token->type == OUTPUT_APPEND)
        {
            cmd->output_type = token->type;
            if (minishell->tok[i + 1])
                cmd->output_file = minishell->tok[++i]->word;
        }
        else
        {
            cmd->argv[argc++] = token->word;
        }
        i++;
    }
    if (cmd && cmd->argv)
        cmd->argv[argc] = NULL;
}

