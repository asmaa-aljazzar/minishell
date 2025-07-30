/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:24:08 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/30 10:20:54 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtin(t_minishell *shell)
{
        if (is_builtin(shell->cmd) == 1)
        {
            echo_builtin(shell);
            return (1);
        }
        // if (is_builtin(shell->cmd) == 2)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 3)
        // {
        //     return (1);
        // }
        // if (is_builtin(shell->cmd) == 4)
        // {
        //     return (1);
        // }
        if (is_builtin(shell->cmd) == 5)
        {
            // cd_builtin(shell);
            return (1);
        }
        // if (is_builtin(shell->cmd) == 5)
        // {
        //     return (1);
        // }
        if ((is_builtin(shell->cmd)) == 6)
        {
            env_builtin(shell);
            return(1);
        }
        if (is_builtin(shell->cmd) == 7)
        {
            pwd_builtin(shell);
            return(1);
        }
        // if (is_builtin(shell->cmd) == 8)
        // {
        //     return(1);
        // }
    return (0);
}