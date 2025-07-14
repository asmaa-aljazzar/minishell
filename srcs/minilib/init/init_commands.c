/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:22:25 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/11 20:43:48 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_cmmands(t_minishell *minishell)
{
    int i;
    i = 0;
    while (i < minishell->pipe_count + 1)
    {
    minishell->cmd[i].argv = NULL;
    minishell->cmd[i].input_type = INPUT_NONE;
    minishell->cmd[i].input_file = NULL;
    minishell->cmd[i].output_type = OUTPUT_NONE;
    minishell->cmd[i].output_file = NULL;

    if (i < minishell->pipe_count)
        minishell->cmd[i].next = &minishell->cmd[i + 1];
    else
        minishell->cmd[i].next = NULL;
    i++;
    }
}
