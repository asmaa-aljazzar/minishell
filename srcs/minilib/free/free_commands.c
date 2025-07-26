/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:13:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:27:56 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_commands(t_minishell *minishell)
{
    t_command *current;
    t_command *next;
    
    current = minishell->cmd;
    while (current)
    {
        next = current->next;
        if (current->argv)
            free(current->argv);
        free_file_list(current->input_files);
        free_file_list(current->output_files);
        free(current);
        current = next;
    }
    minishell->cmd = NULL;
}

