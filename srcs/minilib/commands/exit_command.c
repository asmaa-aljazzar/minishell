/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:30:02 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/26 02:56:57 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_command(t_minishell *minishell)
{
	if (strcmp(minishell->input, "exit") == 0)
	{
		check_to_free(minishell);
		free_env(minishell->env);
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
}