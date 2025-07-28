/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_check_cmd_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:19:00 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 16:59:04 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void debug_check_cmd_heredoc(t_command *cmd)
{
    printf("=== DEBUG: Checking command ===\n");
    printf("input_type: %d\n", cmd->input_type);
    printf("input_file: %s\n", cmd->input_file ? cmd->input_file : "(null)");

    if (cmd->input_files)
    {
        printf("input_files array:\n");
        int i = 0;
        while (cmd->input_files[i])
        {
            printf("  [%d]: %s\n", i, cmd->input_files[i]);
            i++;
        }
    }
    else
    {
        printf("input_files: (null)\n");
    }
    printf("==============================\n");
}