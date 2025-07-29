/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:10:45 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/29 10:46:16 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void pwd_builtin(t_minishell *shell)
{
	t_command *cmd;

	cmd = shell->cmd;
	// printf("call pwd\n");
	if (getcwd(shell->buff, sizeof(shell->buff)) != NULL) 
	{
		if (cmd->output_type == OUTPUT_NONE)
			cmd->output_type = STDOUT_FILENO;
		write(STDOUT_FILENO, shell->buff, ft_strlen(shell->buff));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
	{
                perror("getcwd() error");
				shell->exit_code = 1;
    }
}