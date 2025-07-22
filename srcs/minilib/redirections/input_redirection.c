/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:15 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/22 16:58:49 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void input_redirection(t_command *cmd)
{
    if (cmd->input_type == INPUT_FILE)
    {
        int fd = open(cmd->input_file, O_RDONLY);
        if (fd < 0) {
            perror(cmd->input_file);
            exit(ERR_COMMAND_NOT_FOUND);
        }
        dup2(fd, STDIN_FILENO); //redirects standard input (stdin) to come from the file.
        close(fd);
    }
}

