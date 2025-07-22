/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:38:56 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/22 16:56:25 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void output_redirection(t_command *cmd)
{
    if (cmd->output_type == OUTPUT_FILE)
    {
        int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            perror(cmd->output_file);
            exit(ERR_COMMAND_NOT_FOUND);
        }
        dup2(fd, STDOUT_FILENO);// redirects the standard output (stdout) to the file.
        close(fd);
    }
    else if (cmd->output_type == OUTPUT_APPEND)
    {
        int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0) {
            perror(cmd->output_file);
            exit(ERR_COMMAND_NOT_FOUND);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}
