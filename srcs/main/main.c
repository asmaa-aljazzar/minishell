/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baah-moh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/22 17:19:58 by baah-moh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Each new prompt will initialize the rest of elements in the structure.
//* 3. Handle redirections.
//* 4. Forking.
//* 5. Free if allocated or exit.

int main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	t_minishell minishell;

	init(&minishell);
	minishell.env = init_env(&minishell, environ);
	while (1)
	{
		init_shell(&minishell);
		expand_tokens (&minishell);
		//! Start Debug1
		int i = 0;
		if (minishell.tok)
		{
			while (minishell.tok[i])
			{
				if (minishell.tok[i]->word)
				{
					printf("Token [%d]: %s\n", i + 1, minishell.tok[i]->word);
				}
				else
				{
					printf("Token [%d]: (null word)\n", i + 1);
				}
				i++;
			}
		}
		//! End Debug1
		redirection (&minishell);
		// main_fork (&minishell);	 // Todo
		check_to_free(&minishell);
	}
	rl_clear_history();
	return (0);
}
