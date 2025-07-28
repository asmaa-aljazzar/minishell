/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 00:20:47 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 16:07:59 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void compare_commands(t_minishell *shell)
{
        int     redir_status;

        redir_status = handell_redirection(shell);
        if (redir_status > 0) 
                exit(EXIT_SUCCESS);  // Pure redirection handled
        else if (redir_status < 0) 
                exit(EXIT_FAILURE);  // Redirection error
        // Handle normal commands...
        if (is_builtin(shell->cmd))
        {
                exec_builtin(shell);
                exit(shell->exit_code);
        }
        else
        {
                exec_command(shell);
                exit(EXIT_FAILURE);
        }
}
