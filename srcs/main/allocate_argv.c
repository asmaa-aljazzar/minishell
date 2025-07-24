/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_argv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:23:56 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 18:24:49 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Allocate argv for current cmd (+1 for NULL)

void allocate_argv(t_minishell *minishell, int *argc, t_command *cmd, int *i)
{
	if (ft_strncmp(minishell->tok[*i]->word, "|", 1) == 0)
	{
		cmd->argv = malloc(sizeof(char *) * (*argc + 1));
		if (!cmd->argv)
			ft_exit(minishell, "malloc failed", EXIT_FAILURE);
		argc = 0;
		cmd = cmd->next;
	}
	else if (minishell->tok[*i]->type != INPUT_FILE 
		&& minishell->tok[*i]->type != INPUT_HEREDOC 
		&& minishell->tok[*i]->type != OUTPUT_FILE
		&& minishell->tok[*i]->type != OUTPUT_APPEND)
	{
		argc++;
	}
}