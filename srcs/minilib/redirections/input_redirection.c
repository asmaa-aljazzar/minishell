/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:31:15 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:23:59 by aaljazza         ###   ########.fr       */
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
                //free everything
                exit(ERR_COMMAND_NOT_FOUND);
            } 
            if((dup2(fd, STDIN_FILENO) < 0)) 
            {
                    perror("dup2");
                    close(fd);
                    //free everything
                    exit(EXIT_FAILURE);
            }
            //redirects standard input (stdin) to come from the file.
            close(fd);
    }
}