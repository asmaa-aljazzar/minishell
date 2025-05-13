/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 06:45:44 by aaljazza          #+#    #+#             */
/*   Updated: 2025/05/13 07:42:24 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    init_cmd (t_cmd *cmd)
{
    cmd->append = 42; // to know if >> or >
    cmd->args = NULL; // save the  
    cmd->infile = NULL; // for < and <<
    cmd->outfile = NULL; //use for >> and > 
    cmd->next = NULL; // used for pipe commands to link them
}