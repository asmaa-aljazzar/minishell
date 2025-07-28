/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 12:44:57 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 18:45:20 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	handle_eof(t_minishell *minishell)
{
	if (!minishell->input)
	{
		printf("exit\n");
		free_env(minishell->env);
		free_2d(minishell->envp);
		rl_clear_history();
		exit(0);
	}
}

