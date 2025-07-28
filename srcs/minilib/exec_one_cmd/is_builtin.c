/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_buitin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:22:38 by baah-moh          #+#    #+#             */
/*   Updated: 2025/07/28 22:42:18 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
int is_builtin(t_command *cmd)
{
    int i;
    if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);

    i = 0;
        // if (ft_strncmp(cmd->argv[i], "echo", 5) == 0)
        //     return(1);
        // else if(ft_strncmp(cmd->argv[i], "export", 7) == 0)
        //     return(2);
        // else if(ft_strncmp(cmd->argv[i], "exit", 5) == 0)
        //     return(3);
        // else if(ft_strncmp(cmd->argv[i], "unset", 6) == 0)
        //     return(4);
        // else if(ft_strncmp(cmd->argv[i], "cd", 3) == 0)
        //     return(5);
        if(ft_strncmp(cmd->argv[i], "env", 4) == 0)
            return (6);
        else if(ft_strncmp(cmd->argv[i], "pwd", 4) == 0)
            return(7);
        // else if(ft_strncmp(cmd->argv[i], "history", 8) == 0)
        //     return(8);
    return (0);
}