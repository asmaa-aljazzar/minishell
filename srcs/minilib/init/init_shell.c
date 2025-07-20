/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:35 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/20 19:05:27 by aaljazza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. Display the prompt.
// 2. Read the input line into a buffer.
// 3. Add this line to the history.
// 4. Parsing the input.
// 5. Split it into tokens.
//? 6. Move it into cmd array.
// 7. After Each initialize check for Null.
// 8. exit if error occured
void init_shell(t_minishell *minishell)
{
    // Get user input with readline
    minishell->input = readline(PROMPT);
    if (!minishell->input)
    {
        // Handle EOF (Ctrl+D) gracefully
        printf("exit\n");
        exit(EXIT_SUCCESS); // Clean exit on Ctrl+D
    }

    // Add non-empty commands to history
    if (*minishell->input)
        add_history(minishell->input);

    // Skip processing for empty commands
    if (!*minishell->input)
    {
        free(minishell->input);
        minishell->input = NULL;
        return; // Return to main loop for a new prompt
    }

    // Tokenize the input
    get_tokens(minishell);
    if (!minishell->tok)
        ft_exit(minishell, "ERROR\nNULL tok", EXIT_FAILURE);

    if (minishell->tok[0] && minishell->tok[1] == NULL && ft_strncmp(minishell->tok[0]->word, "env", ft_strlen ("env") + 1) == 0)
    {
        builtin_env(minishell);
        check_to_free(minishell);
        return;
    }

    // Count pipes to determine number of commands
    count_pipe(minishell);

    // Allocate command array
    minishell->cmd = malloc(sizeof(t_command) * (minishell->pipe_count + 1));
    if (!minishell->cmd)
        ft_exit(minishell, "ERROR\nNULL CMD", EXIT_FAILURE);

    minishell->exit_code = 0;
    // Initialize each command structure
    init_cmmands(minishell);
}
