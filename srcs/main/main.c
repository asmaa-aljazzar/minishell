/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:22 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/13 23:07:12 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//? Steps:
//* 1. Initialize some of elements in the structure.
//* 2. Each new prompt will initialize the rest of elements in the structure.
//* 3. Handle redirections.
//* 4. Forking.
//* 5. Free if allocated or exit.

int main(void)
{
	t_minishell minishell;

	init(&minishell);	
	while (1)
	{
		init_shell (&minishell);
		
		//! Start Debug1 
		int i = 0;
		while (minishell.tok[i])
		{
			printf ("Token [%d]: %s\n", i + 1, minishell.tok[i]->word);
			i++;
		}
		//! End Debug1
		
		// redirection (&minishell); // Todo
		// main_fork (&minishell);	 // Todo
		check_to_free (&minishell);
	}
	return (0);
}
