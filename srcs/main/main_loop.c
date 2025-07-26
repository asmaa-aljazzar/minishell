/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 15:32:00 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/24 19:32:10 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize the shell & tokenize the input.
// Run exit command if found.
// Initialize commands pipeline.
// Expand env variables.
// Merge words that not separated by spaces.
// Set argv array for commands nodes.
// Complete convert tokens array into commands linkedlist

void main_loop(t_minishell *minishell)
{
	while (1)
	{
		init_shell(minishell);
		if (!minishell->input || !minishell->tok)
			continue;
		exit_command(minishell);
		init_commands(minishell);
		expand_tokens(minishell);
		merge_words(minishell);
		argv_for_commands(minishell);
		tokens_to_commands(minishell);
		debug_Display_t_command(minishell);
		check_to_free(minishell);
	}
}