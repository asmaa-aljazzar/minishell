/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:13:32 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/14 06:11:21 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_commands(t_minishell *minishell)
{
    int i = 0;
    while (i < minishell->pipe_count + 1)
    {
        if (minishell->cmd[i].argv)
            free_2d(minishell->cmd[i].argv);  // Use free_2d for char**
        if (minishell->cmd[i].input_file)
            free(minishell->cmd[i].input_file);
        if (minishell->cmd[i].output_file)
            free(minishell->cmd[i].output_file);
        i++;
    }
    free(minishell->cmd);
    minishell->cmd = NULL;
}
