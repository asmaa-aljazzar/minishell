/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_for_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:20:45 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 01:54:34 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Last if is for last command after last pipe

void argv_for_commands(t_minishell *minishell)
{
	t_command *cmd = minishell->cmd;
	int i = 0;
	int argc = 0;

	while (minishell->tok[i])
	{
		allocate_argv(minishell, &argc, &cmd, &i);
		i++;
	}
	if (cmd)
	{
		cmd->argv = malloc(sizeof(char *) * (argc + 1));
		if (!cmd->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
	}
}
