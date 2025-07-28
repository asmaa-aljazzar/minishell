/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_empty_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:45:02 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/25 21:31:30 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include"minishell.h"

// int handle_empty_cmd(t_minishell *shell)
// {
//     t_command *cmd = shell->cmd;
    
//     if (!cmd || !cmd->argv || !cmd->argv[0]) {
//         // Handle input redirection (< or <<)
//         if (cmd->input_type == INPUT_FILE || cmd->input_type == INPUT_HEREDOC) {
//             input_redirection(cmd); // Will fail if file doesn't exist
//         }
//         // Handle output redirection (> or >>)
//         if (cmd->output_type == OUTPUT_FILE || cmd->output_type == OUTPUT_APPEND) {
//             output_redirection(cmd); // Will create file if needed
//         }
//         return 1; // Empty command handled
//     }
//     return 0; // Proceed to execution
// }