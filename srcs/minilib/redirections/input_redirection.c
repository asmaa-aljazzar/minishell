/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:15 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/26 22:36:53 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void input_redirection(t_command *cmd)
{
    if (cmd->input_type == INPUT_FILE)
    {
            int fd = open(cmd->input_file, O_RDONLY);
            if (fd < 0)
            {
                perror(cmd->input_file);
                exit(ERR_COMMAND_NOT_FOUND);
            } 
            if((dup2(fd, STDIN_FILENO) < 0)) 
            {
                    perror("dup2");
                    close(fd);
                    exit(EXIT_FAILURE);
            }
            //redirects standard input (stdin) to come from the file.
            close(fd);
    }
}

