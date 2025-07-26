/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:03:54 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 02:49:18 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void tokens_to_commands(t_minishell *minishell)
{
	t_command *cmd;
	t_token *token;

	cmd = minishell->cmd;
	int i = 0;
	int argc = 0;
	while (minishell->tok[i])
	{
		token = minishell->tok[i];
		if_outputPipe(token, &cmd, &argc);
		if_input_filesHeredoc(minishell, token, &cmd, &i);
		if_output_filesAppend(minishell, token, &cmd, &i);
		if (token->type == INUPT_WORD)
			cmd->argv[argc++] = token->word;
		i++;
	}
	if (cmd && cmd->argv)
		cmd->argv[argc] = NULL;
}
