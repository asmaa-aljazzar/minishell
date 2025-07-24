/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:13:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/23 14:29:29 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void free_commands(t_minishell *minishell)
{
    t_command *current = minishell->cmd;
    t_command *next;

    while (current)
    {
        next = current->next;
        if (current->argv)
            free(current->argv);  // just free argv array, not argv[i] strings
        // Do NOT free input_file or output_file — they point to token->word strings!
        free(current);
        current = next;
    }
    minishell->cmd = NULL;
}
