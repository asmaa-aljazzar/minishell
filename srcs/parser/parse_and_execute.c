/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_execute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 06:49:01 by aaljazza          #+#    #+#             */
/*   Updated: 2025/05/13 09:41:29 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void  parse_and_execute (char *input, t_cmd *cmd)
{
    cmd->args = ft_split(input, ' ');
}

// char  **parse_and_execute (char *input)
// {
//     t_cmd cmd;
//     cmd.args = ft_split(input, ' ');
//     return cmd.args;
// }

// int main (int argc, char **argv)
// {
//     int i = 0;
//     t_cmd cmd;
//     if (argc == 2)
//     {
//         cmd.args = parse_and_execute (argv[1]);
    
//          while (cmd.args[i])
//         {
//             printf("[%d]%s\n", i+1, cmd.args[i]);
//             i++;
//         }
//         i = 0;
//         while (cmd.args[i])
//         {
//             free (cmd.args[i]);
//             i++;
//         }
//         free (cmd.args);
//     }
//     return 0;
// }