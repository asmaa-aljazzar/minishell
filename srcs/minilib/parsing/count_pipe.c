/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 20:46:27 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/11 21:52:42 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void count_pipe(t_minishell *minishell)
{
    int i = 0;
    int pipes = 0;
    char *input = minishell->input;
    while (input[i])
    {
        if (input[i] == '|')
            pipes += 1;
        i++;
    }
    minishell->pipe_count = pipes;
}