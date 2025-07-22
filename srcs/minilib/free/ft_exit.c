/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:42:57 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/21 11:47:07 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void ft_exit(t_minishell *minishell, char *str, int status)
{
    // Print error message
    ft_putendl_fd(str, STDERR_FILENO);
    // Free all allocated resources
    check_to_free(minishell);
    rl_clear_history();
    // Exit with status
    minishell->exit_code = status;
    exit(status);
}