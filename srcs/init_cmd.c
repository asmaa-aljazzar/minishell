/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 06:45:44 by aaljazza          #+#    #+#             */
/*   Updated: 2025/05/13 11:04:13 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_cmd (t_cmd *cmd)
{
    cmd->append = 42; // to know if >> or >
    cmd->args = NULL; // save the tokens
    cmd->infile = NULL; // for < and <<
    cmd->outfile = NULL; //use for >> and > 
    cmd->next = NULL; // used for pipe commands to link them
}