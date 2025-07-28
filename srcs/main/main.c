/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/28 18:39:24 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Enter an infinite loop to display prompts.
//* 3. Clear the history if the loop has been broken.
int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_minishell minishell;
	init(&minishell);
	
	minishell.envp = ft_strdup_double (environ);
	minishell.env = init_env(&minishell, environ);
	main_loop(&minishell);
	rl_clear_history();
	return (0);
}