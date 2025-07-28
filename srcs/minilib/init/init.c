/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:38 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/27 01:54:28 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void init(t_minishell *minishell)
{
    // Initialize all pointers to NULL
    minishell->tok = NULL;
    minishell->input = NULL;
    minishell->cmd = NULL;
    
    // Initialize counters to 0
    minishell->tokens_count = 0;
    minishell->pipe_count = 0;
    
    // Clear the buffer
    ft_memset(minishell->buff, 0, sizeof(minishell->buff));
}
