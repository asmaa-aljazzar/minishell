/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaljazza <aaljazza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:14:35 by aaljazza          #+#    #+#             */
/*   Updated: 2025/07/21 12:01:00 by aaljazza         ###   ########.fr       */
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
        minishell->exit_code = EXIT_SUCCESS;
        exit(minishell->exit_code); // Clean exit on Ctrl+D
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
    
    //! Start env_function
    // *export should only update the environment
    //if it runs in the main shellprocess.
    //* If it's part of a pipeline or forked command 
    //(like inside ls | export VAR=val or export VAR && echo), it should not update the environment permanently — only for that child.*/
    //? env command
    if (minishell->tok[0] && minishell->tok[1] == NULL && ft_strncmp(minishell->tok[0]->word, "env", ft_strlen ("env") + 1) == 0)
    {
        builtin_env(minishell);
        check_to_free(minishell);
        return;
    }
    //? export
    else if (minishell->tok[0] && ft_strncmp (minishell->tok[0]->word, "export", ft_strlen ("export") + 1))
    {
        export_builtin (minishell);
        check_to_free (minishell);
        return ;
    }
    //? unset
    else if (minishell->tok[0] && ft_strncmp (minishell->tok[0]->word, "unset", ft_strlen ("unset") + 1))
    {
        unset_builtin (minishell);
        check_to_free (minishell);
        return ;
    }
    //! End env_function
    
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
