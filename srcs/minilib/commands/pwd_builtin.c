/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljzza@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 07:10:45 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/30 10:40:58 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void pwd_builtin(t_minishell *shell)
{
	t_command *cmd;
	char *cwd;

	cmd = shell->cmd;
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		if (cmd->output_type == OUTPUT_NONE)
			cmd->output_type = STDOUT_FILENO;
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		free(cwd); // Important: free memory
	}
	else
	{
		perror("getcwd() error");
		shell->exit_code = 1;
	}
}
