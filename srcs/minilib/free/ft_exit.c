/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:42:57 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 13:07:20 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_exit(t_minishell *minishell, char *str, int status)
{
    if (str && *str)
        ft_putendl_fd(str, STDERR_FILENO);
    if (minishell->cmd)
    {
        free_commands(minishell);
        minishell->cmd = NULL;
    }
    if (minishell->tok)
    {
        free_tokens(minishell->tok);
        minishell->tok = NULL;
    }
    if (minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
    }
    if (minishell->env)
    {
        free_env(minishell->env);
        minishell->env = NULL;
    }
    rl_clear_history();
    minishell->exit_code = status;
    exit(status);
}
