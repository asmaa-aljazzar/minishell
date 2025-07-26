/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_outputPipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 02:17:38 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 02:19:58 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void if_outputPipe(t_token *token, t_command **cmd, int *argc)
{

	if (token->type == OUTPUT_PIPE)
	{
		if (*cmd && (*cmd)->argv)
			(*cmd)->argv[*argc] = NULL;

	
		if (*cmd)
			*cmd = (*cmd)->next;
		*argc = 0;
	}
}