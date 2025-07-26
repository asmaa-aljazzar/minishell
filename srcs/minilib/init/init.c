/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:38 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 18:34:30 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init(t_minishell *minishell)
{
    minishell->tok = NULL;
    minishell->input = NULL;
    minishell->cmd = NULL;
    minishell->tokens_count = 0;
    minishell->pipe_count = 0;
    ft_memset(minishell->buff, 0, sizeof(minishell->buff));
}
