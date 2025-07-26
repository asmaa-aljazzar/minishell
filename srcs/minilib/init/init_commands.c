/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:22:25 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 01:30:46 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_commands(t_minishell *minishell)
{
    t_command *head = NULL;
    t_command *curr = NULL;
    int count = minishell->pipe_count;
    int i = 0;

    while (i <= count)
    {
        t_command *new = malloc(sizeof(t_command));
        if (!new)
            ft_exit(minishell, "malloc failed", EXIT_FAILURE);

        new->argv = NULL;
        new->input_type = INPUT_NONE;
        new->output_type = OUTPUT_NONE;
        new->input_file = NULL;
        new->input_files = NULL;
        new->output_file = NULL;
        new->output_files = NULL;
        new->next = NULL;

        if (!head)
        {
            head = new;
            curr = new;
        }
        else
        {
            curr->next = new;
            curr = new;
        }
        i++;
    }
    minishell->cmd = head;
}
