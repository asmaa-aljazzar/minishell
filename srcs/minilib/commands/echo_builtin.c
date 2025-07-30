/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:09:34 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/30 10:15:43 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void check_n(t_minishell *shell,int *i, int *n)
{
    t_command *cmd;
    int j;

    cmd = shell->cmd;
    *i = 1;
    while(cmd->argv[*i] && ft_strncmp(cmd->argv[*i], "-n", 2) == 0)
    {
        j = 2;
        while (cmd->argv[*i][j] == 'n')
            j++;
        if(cmd->argv[*i][j] != '\0')
            break;
        *n = 0;
        (*i)++;
    }

}
void echo_builtin(t_minishell *shell)
{
	t_command *cmd;
	int i;
    int n;

	cmd = shell->cmd;
    n = 1;
	// printf("call echo\n");
     check_n(shell, &i, &n);

	while(cmd->argv[i])
    {
            write(STDOUT_FILENO, cmd->argv[i], ft_strlen(cmd->argv[i]));
                if(cmd->argv[i + 1])
                    write(STDOUT_FILENO, " ", 1);
            i++;
    }
    if (n)
		write(STDOUT_FILENO, "\n", 1);
    
    shell->exit_code = 0;
}
