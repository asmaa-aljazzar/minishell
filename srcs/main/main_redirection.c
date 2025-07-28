/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:42 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/27 02:19:51 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void main_redirection(t_minishell *shell)
{
    t_command *cmd;

    cmd = shell->cmd;
    while (cmd)
    {
        if (cmd->input_type == INPUT_FILE)
            input_redirection(cmd);
        if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND)
            handle_output_redirection(cmd);
        // if (handle_empty_cmd(shell))
        // {
        //     cmd = cmd->next;
        //     continue;
        // }
        cmd = cmd->next; // move to next command
    }
}
