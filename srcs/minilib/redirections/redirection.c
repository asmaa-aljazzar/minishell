/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:42 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 15:27:31 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reinitialize i, j each new prompt.
// Loop over tokens array to search redirections.
// Set a null termiate in commands array

// void redirection(t_minishell *shell)
// {

	// while (shell->tok[shell->i])
	// {
	// 	redir_compare1(shell);
	// }
	// shell->cmd[shell->j] = NULL;
// }


// void redirection(t_minishell *shell)
// {
//     t_command *cmd;

//     cmd = shell->cmd;
//     while (cmd)
//     {
//         input_redirection(cmd);
// 		output_redirection(cmd);
//         cmd = cmd->next; // move to next command
//     }
// }