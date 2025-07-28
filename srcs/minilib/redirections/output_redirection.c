/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:38:56 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 23:24:30 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void output_redirection_append(t_command *cmd)
{
        int     fd;

        if (cmd->output_type != OUTPUT_APPEND)
        return;

        fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror(cmd->output_file);
                exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
        }
        close(fd);
}

void output_redirection_trunc(t_command *cmd)
{
        int fd;

        if (cmd->output_type != OUTPUT_FILE)
        return;

        fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror(cmd->output_file);
                exit(EXIT_FAILURE);
        }
        if (dup2(fd, STDOUT_FILENO) < 0)
        {
                ft_putstr_fd("minishell: ", STDERR_FILENO);
                perror("dup2");
                close(fd);
                exit(EXIT_FAILURE);
        }
        close(fd);
}
void handle_output_redirection(t_command *cmd)
{
        if (cmd->output_type == OUTPUT_FILE) 
                output_redirection_trunc(cmd);
        else if (cmd->output_type == OUTPUT_APPEND)
                output_redirection_append(cmd);
}